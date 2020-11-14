/**
 * @ Author: Pierre Veysseyre
 * @ Description: DescriptorPoolModel
 */

#pragma once

#include "Vulkan.hpp"
#include "DescriptorPoolSize.hpp"

namespace kF::Graphics
{
    struct DescriptorPoolModel;
};

/** @brief Describe how to create an image */
struct kF::Graphics::DescriptorPoolModel : public VkDescriptorPoolCreateInfo
{
    /** @brief Initialize constructor */
    DescriptorPoolModel(const DescriptorPoolCreateFlags flags_, const std::uint32_t maxSets_,
            const DescriptorPoolSize * const poolSizeBegin, const DescriptorPoolSize * const poolSizeEnd)
        noexcept
        : VkDescriptorPoolCreateInfo {
            sType: VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
            pNext: nullptr,
            flags: ToFlags(flags_),
            maxSets: maxSets_,
            poolSizeCount: static_cast<std::uint32_t>(std::distance(poolSizeBegin, poolSizeEnd)),
            pPoolSizes: poolSizeBegin
        } {}


    /** @brief POD semantics */
    DescriptorPoolModel(const DescriptorPoolModel &other) noexcept = default;
    DescriptorPoolModel(DescriptorPoolModel &&other) noexcept = default;
    DescriptorPoolModel &operator=(const DescriptorPoolModel &other) noexcept = default;
    DescriptorPoolModel &operator=(DescriptorPoolModel &&other) noexcept = default;
};
