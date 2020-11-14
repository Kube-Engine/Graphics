/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Fence
 */

#include <Kube/Core/StringLiteral.hpp>

#include "Renderer.hpp"

using namespace kF;
using namespace kF::Literal;

bool Graphics::Fence::Wait(const FenceHandle * const begin, const FenceHandle * const end, const bool waitAll, const std::uint64_t timeout)
{
    if (auto res = ::vkWaitForFences(Parent().logicalDevice(), std::distance(begin, end), begin, waitAll, timeout); res == VK_TIMEOUT)
        return false;
    else if (res != VK_SUCCESS)
        throw std::runtime_error("Graphics::Fence::Wait: Error on waiting fence(s) '"s + ErrorMessage(res) + '\'');
    return true;
}

void Graphics::Fence::Reset(const FenceHandle * const begin, const FenceHandle * const end) noexcept
{
    ::vkResetFences(Parent().logicalDevice(), std::distance(begin, end), begin);
}

Graphics::Fence::~Fence(void) noexcept
{
    ::vkDestroyFence(parent().logicalDevice(), handle(), nullptr);
}

void Graphics::Fence::createFence(void)
{
    VkFenceCreateInfo semaphoreInfo {
        sType: VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
        pNext: nullptr,
        flags: VK_FENCE_CREATE_SIGNALED_BIT
    };

    if (auto res = ::vkCreateFence(parent().logicalDevice(), &semaphoreInfo, nullptr, &handle()); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::Fence::createFence: Couldn't create semaphore '"s + ErrorMessage(res) + '\'');
}
