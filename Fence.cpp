/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Fence
 */

#include <Kube/Core/Core.hpp>

#include "Renderer.hpp"

using namespace kF;
using namespace kF::Literal;

Graphics::Fence::Fence(Renderer &renderer)
    : VulkanHandler<VkFence>(renderer)
{
    createFence();
}

Graphics::Fence::~Fence(void) noexcept
{
    ::vkDestroyFence(parent().getLogicalDevice(), handle(), nullptr);
}

bool Graphics::Fence::waitToBeSignaled(const std::uint64_t timeout) const
{
    if (auto res = ::vkWaitForFences(parent().getLogicalDevice(), 1, &handle(), true, timeout); res == VK_TIMEOUT)
        return false;
    else if (res != VK_SUCCESS)
        throw std::runtime_error("Graphics::Fence::waitToBeSignaled: Error on waiting fence '"_str + ErrorMessage(res) + '\'');
    return true;
}

void Graphics::Fence::resetFence(void) noexcept
{
    ::vkResetFences(parent().getLogicalDevice(), 1, &handle());
}

void Graphics::Fence::createFence(void)
{
    VkFenceCreateInfo semaphoreInfo {
        sType: VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
        pNext: nullptr,
        flags: VK_FENCE_CREATE_SIGNALED_BIT
    };

    if (auto res = ::vkCreateFence(parent().getLogicalDevice(), &semaphoreInfo, nullptr, &handle()); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::Fence::createFence: Couldn't create semaphore '"_str + ErrorMessage(res) + '\'');
}
