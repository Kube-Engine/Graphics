/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: CommandPool
 */

#include <Kube/Core/StringLiteral.hpp>

#include "Renderer.hpp"

using namespace kF;
using namespace kF::Literal;

Graphics::CommandPool::CommandPool(Renderer &renderer, const QueueType queueType, const Lifecycle lifecycle)
    : VulkanHandle<VkCommandPool>(renderer)
{
    createCommandPool(queueType, lifecycle);
}

Graphics::CommandPool::~CommandPool(void)
{
    ::vkDestroyCommandPool(parent().logicalDevice(), handle(), nullptr);
}

void Graphics::CommandPool::remove(const CommandHandle command)
{
    ::vkFreeCommandBuffers(parent().logicalDevice(), handle(), 1u, &command);
}

void Graphics::CommandPool::clear(void)
{
    ::vkResetCommandPool(parent().logicalDevice(), handle(), VkCommandPoolResetFlags());
}

void Graphics::CommandPool::createCommandPool(const QueueType queueType, const Lifecycle lifecycle)
{
    constexpr auto GetFlags = [](const Lifecycle lifecycle) -> VkCommandPoolCreateFlags {
        switch (lifecycle) {
        case Lifecycle::Manual:
            return VkCommandPoolCreateFlags();
        case Lifecycle::Auto:
            return VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
        }
    };

    VkCommandPoolCreateInfo commandPoolInfo {
        sType: VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
        pNext: nullptr,
        flags: GetFlags(lifecycle),
        queueFamilyIndex: parent().queueManager().queueDescriptor(QueueType::Graphics).queueFamilyIndex
    };

    if (auto res = ::vkCreateCommandPool(parent().logicalDevice(), &commandPoolInfo, nullptr, &handle()); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::CommandPool::createCommandPool: Couldn't create command pool '"s + ErrorMessage(res) + '\'');
}

void Graphics::CommandPool::allocateCommands(CommandHandle * const commandFrom, CommandHandle * const commandTo, const CommandLevel level)
{
    VkCommandBufferAllocateInfo commandInfo {
        sType: VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        pNext: nullptr,
        commandPool: handle(),
        level: static_cast<VkCommandBufferLevel>(level),
        commandBufferCount: static_cast<std::uint32_t>(std::distance(commandFrom, commandTo))
    };

    if (auto res = ::vkAllocateCommandBuffers(parent().logicalDevice(), &commandInfo, commandFrom); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::CommandPool::
        : Couldn't allocate command buffers '"s + ErrorMessage(res) + '\'');
}

void Graphics::CommandPool::recordRender(const RenderModel * const modelFrom, const RenderModel * const modelTo,
        CommandHandle * const commandFrom, CommandHandle * const commandTo,
        const VkCommandBufferBeginInfo &commandBeginInfo)
{
    static const VkClearValue ClearColor = { 0.0f, 0.0f, 0.0f, 1.0f };

    VkRenderPassBeginInfo renderPassBeginInfo {
        sType: VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
        pNext: nullptr,
        renderPass: parent().renderPass(),
        frameBuffer: VkFrameBuffer(),
        renderArea: VkRect2D { { 0, 0 }, parent().swapchain().extent() },
        clearValueCount: 1u,
        pClearValues: &ClearColor
    };

    const auto &renderModel = model.as<RenderModel>();
    const auto &frameBuffers = parent().frameBufferManager().frameBuffers();
    auto &pipeline = parent().pipelinePool().getPipeline(renderModel.pipeline);
    auto max = frameBuffers.size();
    auto buffers = parent().bufferPool().collectBuffers(renderModel.buffers);

    kFAssert(buffers.size() == renderModel.offsets.size(),
        throw std::runtime_error("Graphics::CommandPool::recordCommand: Invalid buffer offsets"));
    for (auto i = 0u; i < max; ++i) {
        auto &command = commands[i];
        renderPassBeginInfo.frameBuffer = frameBuffers[i];
        if (auto res = ::vkBeginCommandBuffer(command, &commandBeginInfo); res != VK_SUCCESS)
            throw std::runtime_error("Graphics::CommandPool::recordCommand: Couldn't begin command buffer " + std::to_string(i) + " '" + ErrorMessage(res) + '\'');
        ::vkCmdBeginRenderPass(command, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
        ::vkCmdBindPipeline(command, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
        if (!buffers.empty())
            ::vkCmdBindVertexBuffers(command, 0, buffers.size(), buffers.data(), renderModel.offsets.data());
        ::vkCmdDraw(command, renderModel.vertexCount, renderModel.instanceCount, renderModel.vertexOffset, renderModel.instanceOffset);
        ::vkCmdEndRenderPass(command);
        if (auto res = ::vkEndCommandBuffer(command); res != VK_SUCCESS)
           throw std::runtime_error("Graphics::CommandPool::recordCommand: Couldn't record command buffer " + std::to_string(i) + " '" + ErrorMessage(res) + '\'');
    }
}

void Graphics::CommandPool::recordTransfer(const TransferModel * const modelFrom, const TransferModel * const modelTo,
        CommandHandle * const commandFrom, CommandHandle * const commandTo,
        const VkCommandBufferBeginInfo &commandBeginInfo)
{
}