/**
 * @ Author: Pierre Veysseyre
 * @ Description: DescriptorPoolSize
 */

#pragma once

#include "Vulkan.hpp"

namespace kF::Graphics
{
    struct DescriptorPoolSize;
};

/** @brief Describe how to create an image */
struct kF::Graphics::DescriptorPoolSize : public VkDescriptorPoolSize
{
    /** @brief Initialize constructor */
    DescriptorPoolSize(const DescriptorType type_, const std::uint32_t descriptorCount_)
        noexcept
        : VkDescriptorPoolSize {
            type: static_cast<VkDescriptorType>(type_),
            descriptorCount: descriptorCount_
        } {}


    /** @brief POD semantics */
    DescriptorPoolSize(const DescriptorPoolSize &other) noexcept = default;
    DescriptorPoolSize(DescriptorPoolSize &&other) noexcept = default;
    DescriptorPoolSize &operator=(const DescriptorPoolSize &other) noexcept = default;
    DescriptorPoolSize &operator=(DescriptorPoolSize &&other) noexcept = default;
};
