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
    if (const auto res = ::vkCreateDescriptorPool(parent().logicalDevice(), &model, nullptr, &handle()); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::DescriptorPool::createDescriptorPool: Couldn't create descriptor pool '"s + ErrorMessage(res) + '\'');
}

void Graphics::DescriptorPool::allocateDescriptorSets(
        const DescriptorSetLayoutHandle * const layoutBegin, const DescriptorSetLayoutHandle * const layoutEnd,
        DescriptorSetHandle * const descriptorSetBegin, DescriptorSetHandle * const descriptorSetEnd)
{
    kFAssert(std::distance(layoutBegin, layoutEnd) == std::distance(descriptorSetBegin, descriptorSetEnd),
        throw std::logic_error("Graphics::DescriptorPool::allocateDescriptorSets: Distance between descriptorSetBegin & descriptorSetEnd doesn't correspond to the input layouts distance !"));

    const VkDescriptorSetAllocateInfo allocInfo {
        sType: VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        pNext: nullptr,
        descriptorPool: handle(),
        descriptorSetCount: static_cast<std::uint32_t>(std::distance(layoutBegin, layoutEnd)),
        pSetLayouts: layoutBegin
    };

    if (const auto res = ::vkAllocateDescriptorSets(parent().logicalDevice(), &allocInfo, descriptorSetBegin); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::DescriptorPool::allocateDescriptorSets: Couldn't allocate descriptor sets '"s + ErrorMessage(res) + '\'');
}