/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: CommandPool
 */

#include <Kube/Core/StringLiteral.hpp>

#include "Renderer.hpp"
#include "CommandPool.hpp"

using namespace kF;
using namespace kF::Literal;

Graphics::CommandPool::CommandPool(Renderer &renderer, const QueueType queueType, const Lifecycle lifecycle)
    : VulkanHandle<VkCommandPool>(renderer)
{
    createCommandPool(queueType, lifecycle);
}

Graphics::CommandPool::~CommandPool(void) noexcept
{
    ::vkDestroyCommandPool(parent().logicalDevice(), handle(), nullptr);
}

void Graphics::CommandPool::remove(const CommandHandle * const commandBegin, const CommandHandle * const commandEnd) noexcept
{
    ::vkFreeCommandBuffers(
        parent().logicalDevice(), handle(),
        static_cast<std::size_t>(std::distance(commandBegin, commandEnd)), commandBegin
    );
}

void Graphics::CommandPool::clear(void) noexcept
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
        default:
            return VkCommandPoolCreateFlags();
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

void Graphics::CommandPool::allocateCommands(const CommandLevel level, CommandHandle * const commandFrom, CommandHandle * const commandTo)
{
    VkCommandBufferAllocateInfo commandInfo {
        sType: VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        pNext: nullptr,
        commandPool: handle(),
        level: static_cast<VkCommandBufferLevel>(level),
        commandBufferCount: static_cast<std::uint32_t>(std::distance(commandFrom, commandTo))
    };

    if (auto res = ::vkAllocateCommandBuffers(parent().logicalDevice(), &commandInfo, commandFrom); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::CommandPool::allocateCommands: Couldn't allocate command buffers '"s + ErrorMessage(res) + '\'');
}