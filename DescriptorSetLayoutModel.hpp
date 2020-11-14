/**
 * @ Author: Pierre Veysseyre
 * @ Description: DescriptorSetLayoutModel
 */

#pragma once

#include "Vulkan.hpp"
#include "DescriptorSetLayoutBinding.hpp"

namespace kF::Graphics
{
    struct DescriptorSetLayoutModel;
};

/** @brief Describe how to create an image */
struct kF::Graphics::DescriptorSetLayoutModel : public VkDescriptorSetLayoutCreateInfo
{
    /** @brief Initialize constructor */
    DescriptorSetLayoutModel(const DescriptorSetLayoutCreateFlags flags_,
            const DescriptorSetLayoutBinding * const bindingBegin, const DescriptorSetLayoutBinding * const bindingEnd)
        noexcept
        : VkDescriptorSetLayoutCreateInfo {
            sType: VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
            pNext: nullptr,
            flags: ToFlags(flags_),
            bindingCount: static_cast<std::uint32_t>(std::distance(bindingBegin, bindingEnd)),
            pBindings: bindingBegin
        } {}


    /** @brief POD semantics */
    DescriptorSetLayoutModel(const DescriptorSetLayoutModel &other) noexcept = default;
    DescriptorSetLayoutModel(DescriptorSetLayoutModel &&other) noexcept = default;
    DescriptorSetLayoutModel &operator=(const DescriptorSetLayoutModel &other) noexcept = default;
    DescriptorSetLayoutModel &operator=(DescriptorSetLayoutModel &&other) noexcept = default;
};
