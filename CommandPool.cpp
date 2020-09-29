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

CommandPool::CommandPool(Renderer &renderer)
    : VulkanHandler<VkCommandPool>(renderer)
{
#ifndef KUBE_NO_DYNAMIC_RESIZE
    _viewport.maxDepth = 1.0f;
#endif
    createCommandPool();
    onViewSizeChanged();
}

CommandPool::~CommandPool(void)
{
    ::vkDestroyCommandPool(parent().getLogicalDevice(), handle(), nullptr);
}

CommandIndex CommandPool::addCommand(const CommandModel &model)
{
    auto index = 1u;

    if (!_commandMap.empty())
        index = _commandMap.crbegin()->first + 1;
    auto &pair = _commandMap.emplace_back(index, std::make_unique<Commands>(parent().getFramebufferHandler().getFramebuffers().size()));
    allocateCommands(model, *pair.second);
    recordCommands(model, *pair.second);
    _modelMap.emplace_back(std::make_unique<CommandModel>(model));
    return index;
}

void CommandPool::removeCommand(const CommandIndex index)
{
    auto it = findCommand(index);
    auto mit = _modelMap.begin() + std::distance(_commandMap.begin(), it);

    if (it == _commandMap.end())
        throw std::runtime_error("Renderer::removeCommand: Couldn't find command with index '" + std::to_string(index) + '\'');
    destroyCommands(*it->second);
    _commandMap.erase(it);
    _modelMap.erase(mit);
}

Commands &CommandPool::getCommands(const CommandIndex index)
{
    auto it = findCommand(index);

    if (it == _commandMap.end())
        throw std::runtime_error("CommandPool::getCommand: Couldn't get command of index '" + std::to_string(index) + '\'');
    return *it->second;
}

const Commands &CommandPool::getCommands(const CommandIndex index) const
{
    auto it = findCommand(index);

    if (it == _commandMap.end())
        throw std::runtime_error("CommandPool::getCommands: Couldn't get command of index '" + std::to_string(index) + '\'');
    return *it->second;
}

void CommandPool::onViewSizeChanged(void)
{
#ifndef KUBE_NO_DYNAMIC_RESIZE
    auto width = parent().getSwapchain().getExtent().width, height = parent().getSwapchain().getExtent().height;
    _viewport.width = width;
    _viewport.height = height;
    _scissor.extent.width = width;
    _scissor.extent.height = height;
#endif
    for (auto it = _modelMap.begin(); const auto &pair : _commandMap) {
        destroyCommands(*pair.second);
        allocateCommands(**it, *pair.second);
        recordCommands(**it, *pair.second);
        ++it;
    }
}

void CommandPool::createCommandPool(void)
{
    VkCommandPoolCreateInfo commandPoolInfo {
        .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
        .pNext = nullptr,
        .flags = VkCommandPoolCreateFlags(),
        .queueFamilyIndex = parent().getQueueHandler().getQueueDescriptor(QueueType::Graphics).queueFamilyIndex
    };

    if (auto res = ::vkCreateCommandPool(parent().getLogicalDevice(), &commandPoolInfo, nullptr, &handle()); res != VK_SUCCESS)
        throw std::runtime_error("CommandPool::createCommandPool: Couldn't create command pool '"_str + ErrorMessage(res) + '\'');
}

void CommandPool::allocateCommands(const CommandModel &model, Commands &commands)
{
    VkCommandBufferAllocateInfo commandInfo {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .pNext = nullptr,
        .commandPool = handle(),
        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandBufferCount = static_cast<std::uint32_t>(commands.size())
    };

    if (auto res = ::vkAllocateCommandBuffers(parent().getLogicalDevice(), &commandInfo, commands.data()); res != VK_SUCCESS)
        throw std::runtime_error("CommandPool::addCommand: Couldn't allocate command buffers '"_str + ErrorMessage(res) + '\'');
}

void CommandPool::recordCommands(const CommandModel &model, Commands &commands)
{
    static const VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
    VkCommandBufferBeginInfo commandBeginInfo {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .pNext = nullptr,
        .flags = VkCommandBufferUsageFlags(),
        .pInheritanceInfo = nullptr
    };
    VkRenderPassBeginInfo renderPassBeginInfo {
        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
        .pNext = nullptr,
        .renderPass = parent().getRenderPass(),
        .framebuffer = VkFramebuffer(),
        .renderArea = VkRect2D { { 0, 0 }, parent().getSwapchain().getExtent() },
        .clearValueCount = 1,
        .pClearValues = &clearColor
    };
    const auto &framebuffers = parent().getFramebufferHandler().getFramebuffers();
    auto &pipeline = parent().getPipelinePool().getPipeline(model.pipeline);
    auto max = framebuffers.size();
    auto buffers = parent().getBufferPool().collectBuffers(model.renderModel.buffers);

    kFAssert(buffers.size() == model.renderModel.offsets.size(),
        throw std::runtime_error("CommandPool::recordCommand: Invalid buffer offsets"));
    for (auto i = 0u; i < max; ++i) {
        auto &command = commands[i];
        renderPassBeginInfo.framebuffer = framebuffers[i];
        if (auto res = ::vkBeginCommandBuffer(command, &commandBeginInfo); res != VK_SUCCESS)
            throw std::runtime_error("CommandPool::recordCommand: Couldn't begin command buffer " + std::to_string(i) + " '" + ErrorMessage(res) + '\'');
        ::vkCmdBeginRenderPass(command, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
        ::vkCmdBindPipeline(command, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
#ifndef KUBE_NO_DYNAMIC_RESIZE
        ::vkCmdSetViewport(command, 0, 1, &_viewport);
        ::vkCmdSetScissor(command, 0, 1, &_scissor);
#endif
        if (!buffers.empty())
            ::vkCmdBindVertexBuffers(command, 0, buffers.size(), buffers.data(), model.renderModel.offsets.data());
        ::vkCmdDraw(command, model.renderModel.vertexCount, model.renderModel.instanceCount, model.renderModel.vertexOffset, model.renderModel.instanceOffset);
        ::vkCmdEndRenderPass(command);
        if (auto res = ::vkEndCommandBuffer(command); res != VK_SUCCESS)
           throw std::runtime_error("CommandPool::recordCommand: Couldn't record command buffer " + std::to_string(i) + " '" + ErrorMessage(res) + '\'');
    }
}

void CommandPool::destroyCommands(Commands &commands) noexcept
{
    if (!commands.empty())
        ::vkFreeCommandBuffers(parent().getLogicalDevice(), handle(), static_cast<std::uint32_t>(commands.size()), commands.data());
}