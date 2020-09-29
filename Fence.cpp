/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Fence
 */

#include <Kube/Core/Core.hpp>

#include "Renderer.hpp"

using namespace kF;
using namespace kF::Literal;

Fence::Fence(Renderer &renderer)
    : VulkanHandler<VkFence>(renderer)
{
    createFence();
}

Fence::~Fence(void)
{
    ::vkDestroyFence(parent().getLogicalDevice(), handle(), nullptr);
}

bool Fence::waitToBeSignaled(const std::uint64_t timeout) const
{
    if (auto res = ::vkWaitForFences(parent().getLogicalDevice(), 1, &handle(), true, timeout); res == VK_TIMEOUT)
        return false;
    else if (res != VK_SUCCESS)
        throw std::runtime_error("Fence::waitToBeSignaled: Error on waiting fence '"_str + ErrorMessage(res) + '\'');
    return true;
}

void Fence::resetFence(void)
{
    ::vkResetFences(parent().getLogicalDevice(), 1, &handle());
}

void Fence::createFence(void)
{
    VkFenceCreateInfo semaphoreInfo {
        .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
        .pNext = nullptr,
        .flags = VK_FENCE_CREATE_SIGNALED_BIT
    };

    if (auto res = ::vkCreateFence(parent().getLogicalDevice(), &semaphoreInfo, nullptr, &handle()); res != VK_SUCCESS)
        throw std::runtime_error("Fence::createFence: Couldn't create semaphore '"_str + ErrorMessage(res) + '\'');
}
