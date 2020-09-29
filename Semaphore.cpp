/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Semaphore
 */

#include <Kube/Core/Core.hpp>

#include "Renderer.hpp"

using namespace kF;
using namespace kF::Literal;

Semaphore::Semaphore(Renderer &renderer)
    : VulkanHandler<VkSemaphore>(renderer)
{
    createSemaphore();
}

Semaphore::~Semaphore(void)
{
    ::vkDestroySemaphore(parent().getLogicalDevice(), handle(), nullptr);
}

void Semaphore::createSemaphore(void)
{
    VkSemaphoreCreateInfo semaphoreInfo {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
        .pNext = nullptr,
        .flags = VkSemaphoreCreateFlags()
    };

    if (auto res = ::vkCreateSemaphore(parent().getLogicalDevice(), &semaphoreInfo, nullptr, &handle()); res != VK_SUCCESS)
        throw std::runtime_error("Semaphore::createSemaphore: Couldn't create semaphore '"_str + ErrorMessage(res) + '\'');
}