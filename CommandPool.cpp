/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: CommandPool
 */

#include <algorithm>

#include <Kube/Core/Core.hpp>
#include <Kube/Core/Assert.hpp>

#include "Renderer.hpp"

using namespace kF;
using namespace kF::Literal;

Graphics::CommandPool::CommandPool(Renderer &renderer, const Type type)
    : VulkanHandler<VkCommandPool>(renderer)
{
#ifdef KUBE_HAS_DYNAMIC_WINDOW_RESIZE
    _viewport.maxDepth = 1.0f;
#endif
    createCommandPool(type);
    onViewSizeChanged();
}

Graphics::CommandPool::~CommandPool(void) noexcept
{
    ::vkDestroyCommandPool(parent().getLogicalDevice(), handle(), nullptr);
}

Graphics::CommandIndex Graphics::CommandPool::addCommand(const CommandModel &model)
{
    auto index = 1u;
    auto size = 1u;
    const auto isManual = model.lifecycle == CommandModel::Lifecycle::Manual;
    const auto isRender = model.type() == CommandModel::Type::Render;

    if (!_commandMap.empty())
        index = _commandMap.crbegin()->first + 1;
    if (isRender)
        size = parent().getFramebufferHandler().getFramebuffers().size();
    auto &pair = _commandMap.emplace_back(index, std::make_unique<Commands>(size));
    allocateCommands(model, *pair.second);
    if (isRender)
        recordDrawCommands(model, *pair.second);
    else
        recordTransferCommands(model, *pair.second);
    if (isManual)
        _modelMap.emplace_back(std::make_unique<CommandModel>(model));
    return index;
}

void Graphics::CommandPool::removeCommand(const CommandIndex index)
{
    auto it = findCommand(index);
    auto mit = _modelMap.begin() + std::distance(_commandMap.begin(), it);

    if (it == _commandMap.end())
        throw std::runtime_error("Renderer::removeCommand: Couldn't find command with index '" + std::to_string(index) + '\'');
    destroyCommands(*it->second);
    _commandMap.erase(it);
    _modelMap.erase(mit);
}

Graphics::Commands &Graphics::CommandPool::getCommands(const CommandIndex index)
{
    auto it = findCommand(index);

    if (it == _commandMap.end())
        throw std::runtime_error("Graphics::CommandPool::getCommand: Couldn't get command of index '" + std::to_string(index) + '\'');
    return *it->second;
}

const Graphics::Commands &Graphics::CommandPool::getCommands(const CommandIndex index) const
{
    auto it = findCommand(index);

    if (it == _commandMap.end())
        throw std::runtime_error("Graphics::CommandPool::getCommands: Couldn't get command of index '" + std::to_string(index) + '\'');
    return *it->second;
}

void Graphics::CommandPool::onViewSizeChanged(void)
{
#ifdef KUBE_HAS_DYNAMIC_WINDOW_RESIZE
    auto width = parent().getSwapchain().getExtent().width, height = parent().getSwapchain().getExtent().height;
    _viewport.width = width;
    _viewport.height = height;
    _scissor.extent.width = width;
    _scissor.extent.height = height;
#endif
    for (auto it = _modelMap.begin(); const auto &pair : _commandMap) {
        destroyCommands(*pair.second);
        allocateCommands(**it, *pair.second);
        if ((**it).type() == CommandModel::Type::Render)
            recordDrawCommands(**it, *pair.second);
        else
            recordTransferCommands(**it, *pair.second);
        ++it;
    }
}

void Graphics::CommandPool::createCommandPool(const Type type)
{
    constexpr auto GetCreateFlags = [](const Type type) -> CommandPoolCreateFlags {
        switch (type) {
        case Type::ManualAndOneTimeSubmit:
            return CommandPoolCreateFlags();
        case Type::OneTimeSubmitOnly:
            return VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        default:
            return CommandPoolCreateFlags();
        }
    };

    VkCommandPoolCreateInfo commandPoolInfo {
        sType: VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
        pNext: nullptr,
        flags: GetCreateFlags(type),
        queueFamilyIndex: parent().getQueueHandler().getQueueDescriptor(QueueType::Graphics).queueFamilyIndex
    };

    if (auto res = ::vkCreateCommandPool(parent().getLogicalDevice(), &commandPoolInfo, nullptr, &handle()); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::CommandPool::createCommandPool: Couldn't create command pool '"_str + ErrorMessage(res) + '\'');
}

void Graphics::CommandPool::allocateCommands(const CommandModel &model, Commands &commands)
{
    VkCommandBufferAllocateInfo commandInfo {
        sType: VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        pNext: nullptr,
        commandPool: handle(),
        level: VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        commandBufferCount: static_cast<std::uint32_t>(commands.size())
    };

    if (auto res = ::vkAllocateCommandBuffers(parent().getLogicalDevice(), &commandInfo, commands.data()); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::CommandPool::addCommand: Couldn't allocate command buffers '"_str + ErrorMessage(res) + '\'');
}


void Graphics::CommandPool::recordTransferCommands(const CommandModel &model, Commands &commands)
{
    auto &cmd = commands[0];
    auto &transferModel = model.as<TransferModel>();
    VkCommandBufferBeginInfo beginInfo {
        sType: VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        flags: VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT
    };
    VkBufferCopy copyRegion {
        srcOffset: transferModel.sourceOffset,
        dstOffset: transferModel.destinationOffset,
        size: transferModel.size
    };

    if (auto res = ::vkBeginCommandBuffer(cmd, &beginInfo); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::CommandPool::addCommand: Couldn't begin command buffers '"_str + ErrorMessage(res) + '\'');

    vkCmdCopyBuffer(cmd, transferModel.source, transferModel.destination, 1, &copyRegion);
    if (auto res = ::vkEndCommandBuffer(cmd); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::CommandPool::addCommand: Couldn't copy command buffers '"_str + ErrorMessage(res) + '\'');

    // _commandMap.emplace_back()}
}

void Graphics::CommandPool::recordDrawCommands(const CommandModel &model, Commands &commands)
{
    constexpr auto GetUsageFlags = [](const CommandModel::Lifecycle lifecycle) -> CommandBufferUsageFlags {
        switch (lifecycle) {
        case CommandModel::Lifecycle::Manual:
            return CommandBufferUsageFlags();
        case CommandModel::Lifecycle::OneTimeSubmit:
            return VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        default:
            return CommandBufferUsageFlags();
        }
    };

    static const VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };

    VkCommandBufferBeginInfo commandBeginInfo {
        sType: VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        pNext: nullptr,
        flags: GetUsageFlags(model.lifecycle),
        pInheritanceInfo: nullptr
    };
    VkRenderPassBeginInfo renderPassBeginInfo {
        sType: VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
        pNext: nullptr,
        renderPass: parent().getRenderPass(),
        framebuffer: VkFramebuffer(),
        renderArea: VkRect2D { { 0, 0 }, parent().getSwapchain().getExtent() },
        clearValueCount: 1,
        pClearValues: &clearColor
    };
    const auto &renderModel = model.as<RenderModel>();
    const auto &framebuffers = parent().getFramebufferHandler().getFramebuffers();
    auto &pipeline = parent().getPipelinePool().getPipeline(renderModel.pipeline);
    auto max = framebuffers.size();
    auto buffers = parent().getBufferPool().collectBuffers(renderModel.buffers);

    kFAssert(buffers.size() == renderModel.offsets.size(),
        throw std::runtime_error("Graphics::CommandPool::recordCommand: Invalid buffer offsets"));
    for (auto i = 0u; i < max; ++i) {
        auto &command = commands[i];
        renderPassBeginInfo.framebuffer = framebuffers[i];
        if (auto res = ::vkBeginCommandBuffer(command, &commandBeginInfo); res != VK_SUCCESS)
            throw std::runtime_error("Graphics::CommandPool::recordCommand: Couldn't begin command buffer " + std::to_string(i) + " '" + ErrorMessage(res) + '\'');
        ::vkCmdBeginRenderPass(command, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
        ::vkCmdBindPipeline(command, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
#ifdef KUBE_HAS_DYNAMIC_WINDOW_RESIZE
        ::vkCmdSetViewport(command, 0, 1, &_viewport);
        ::vkCmdSetScissor(command, 0, 1, &_scissor);
#endif
        if (!buffers.empty())
            ::vkCmdBindVertexBuffers(command, 0, buffers.size(), buffers.data(), renderModel.offsets.data());
        ::vkCmdDraw(command, renderModel.vertexCount, renderModel.instanceCount, renderModel.vertexOffset, renderModel.instanceOffset);
        ::vkCmdEndRenderPass(command);
        if (auto res = ::vkEndCommandBuffer(command); res != VK_SUCCESS)
           throw std::runtime_error("Graphics::CommandPool::recordCommand: Couldn't record command buffer " + std::to_string(i) + " '" + ErrorMessage(res) + '\'');
    }
}

void Graphics::CommandPool::destroyCommands(Commands &commands) noexcept
{
    if (!commands.empty())
        ::vkFreeCommandBuffers(parent().getLogicalDevice(), handle(), static_cast<std::uint32_t>(commands.size()), commands.data());
}