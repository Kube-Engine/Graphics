/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: DescriptorPool
 */

#include <Kube/Core/StringLiteral.hpp>

#include "Renderer.hpp"
#include "DescriptorPool.hpp"

using namespace kF;
using namespace kF::Literal;

Graphics::DescriptorPool::~DescriptorPool(void) noexcept
{
    ::vkDestroyDescriptorPool(parent().logicalDevice(), handle(), nullptr);
}

void Graphics::DescriptorPool::createDescriptorPool(const DescriptorPoolModel &model)
{
    if (auto res = ::vkCreateDescriptorPool(parent().logicalDevice(), &model, nullptr, &handle()); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::DescriptorPool::createDescriptorPool: Couldn't create descriptor pool '"s + ErrorMessage(res) + '\'');
}
