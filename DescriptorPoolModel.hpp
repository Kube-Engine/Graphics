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
    /** @brief Make a unique (one descriptor) Uniform Buffer Descriptor */
    [[nodiscard]] static DescriptorPoolModel MakeUniformBufferPool(const std::uint32_t maxSets, const DescriptorPoolSize &poolSize) noexcept;

    [[nodiscard]] static DescriptorPoolModel MakeUniformBufferPool(const std::uint32_t maxSets,
            const DescriptorPoolSize *poolSizeBegin, const DescriptorPoolSize *poolSizeEnd) noexcept;


    /** @brief Initialize constructor */
    DescriptorPoolModel(const DescriptorPoolCreateFlags flags_, const std::uint32_t maxSets_,
            const DescriptorPoolSize const *poolSizeBegin, const poolSize const *poolSizeEnd)
        noexcept
        : VkDescriptorPoolCreateInfo {
            sType: VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
            pNext: nullptr,
            flags: ToFlags(flags_),
            maxSets: maxSets_,
            poolSizeCount: static_cast<std::uint32_t>(std::distance(poolSizeBegin, poolSizeEnd)),
            pPoolSizes: bindingBegin
        } {}


    /** @brief POD semantics */
    DescriptorPoolModel(const DescriptorPoolModel &other) noexcept = default;
    DescriptorPoolModel(DescriptorPool &&other) noexcept = default;
    DescriptorPoolModel &operator=(const DescriptorPoolModel &other) noexcept = default;
    DescriptorPoolModel &operator=(DescriptorPoolModel &&other) noexcept = default;
};

#include "DescriptorPoolModel.ipp"