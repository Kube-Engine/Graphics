/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Semaphore
 */

#include <Kube/Core/StringLiteral.hpp>

#include "Renderer.hpp"
#include "Semaphore.hpp"

using namespace kF;
using namespace kF::Literal;


Graphics::Semaphore::~Semaphore(void) noexcept
{
    ::vkDestroySemaphore(parent().logicalDevice(), handle(), nullptr);
}

void Graphics::Semaphore::createSemaphore(void)
{
    VkSemaphoreCreateInfo semaphoreInfo {
        sType: VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
        pNext: nullptr,
        flags: VkSemaphoreCreateFlags()
    };

    if (const auto res = ::vkCreateSemaphore(parent().logicalDevice(), &semaphoreInfo, nullptr, &handle()); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::Semaphore::createSemaphore: Couldn't create semaphore '"s + ErrorMessage(res) + '\'');
}