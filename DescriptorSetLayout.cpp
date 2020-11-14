/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: DescriptorSetLayout
 */

#include <Kube/Core/StringLiteral.hpp>

#include "Renderer.hpp"
#include "DescriptorSetLayout.hpp"

using namespace kF;
using namespace kF::Literal;

Graphics::DescriptorSetLayout::~DescriptorSetLayout(void) noexcept
{
    ::vkDestroyDescriptorSetLayout(parent().logicalDevice(), handle(), nullptr);
}

void Graphics::DescriptorSetLayout::createDescriptorSetLayout(const DescriptorSetLayoutModel &model)
{
    if (const auto res = ::vkCreateDescriptorSetLayout(parent().logicalDevice(), &model, nullptr, &handle()); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::DescriptorSetLayout::createDescriptorSetLayout: Couldn't create descriptor set layout '"s + ErrorMessage(res) + '\'');
}
