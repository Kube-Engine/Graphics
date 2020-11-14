/**
 * @ Author: Pierre Veysseyre
 * @ Description: DescriptorSetLayoutBinding
 */

#pragma once

#include "Vulkan.hpp"

namespace kF::Graphics
{
    struct DescriptorSetLayoutBinding;
};

/** @brief Describe how to create an image */
struct kF::Graphics::DescriptorSetLayoutBinding : public VkDescriptorSetLayoutBinding
{
    [[nodiscard]] static DescriptorSetLayoutBinding MakeUniformBinding(const std::uint32_t binding, const std::uint32_t descriptorCount,
            const ShaderStageFlags shaderStageFlags) noexcept;


    /** @brief Initialize constructor */
    DescriptorSetLayoutBinding(const std::uint32_t binding_, const DescriptorType type_, const std::uint32_t descriptorCount_,
            const ShaderStageFlags shaderStageFlags_, const SamplerHandle * const sampler_)
        noexcept
        : VkDescriptorSetLayoutBinding {
            binding: binding_,
            descriptorType: static_cast<VkDescriptorType>(type_),
            descriptorCount: descriptorCount_,
            stageFlags: ToFlags(shaderStageFlags_),
            pImmutableSamplers: sampler_
        } {}

    /** @brief POD semantics */
    DescriptorSetLayoutBinding(const DescriptorSetLayoutBinding &other) noexcept = default;
    DescriptorSetLayoutBinding(DescriptorSetLayoutBinding &&other) noexcept = default;
    DescriptorSetLayoutBinding &operator=(const DescriptorSetLayoutBinding &other) noexcept = default;
    DescriptorSetLayoutBinding &operator=(DescriptorSetLayoutBinding &&other) noexcept = default;

};

#include "DescriptorSetLayoutBinding.ipp"
