/**
 * @ Author: Pierre Veysseyre
 * @ Description: UniformModel.hpp
 */

#pragma once

#include "Vulkan.hpp"

#include <Core/FlatVector.hpp>

namespace kF::Graphics
{
    struct DescriptorBindingModel;

    using DescriptorBindingModels = kF::Core::FlatVector<DescriptorBindingModel>;
};

/** @brief Describe how to create an image */
struct kF::Graphics::DescriptorBindingModel : public VkDescriptorSetLayoutBinding
{
    /** @brief Initialize constructor */
    DescriptorBindingModel(const uint32_t binding_, const DescriptorType type_, const uint32_t descriptorCount_, const ShaderStageFlags shaderStageFlags_, const VkSampler *sampler_)
        noexcept
        : VkDescriptorSetLayoutBinding {
            binding: binding_,
            descriptorType: static_cast<VkDescriptorType>(type_),
            descriptorCount: descriptorCount_,
            stageFlags: ToFlags(shaderStageFlags_),
            pImmutableSamplers: sampler_
        } {}


    /** @brief POD semantics */
    DescriptorBindingModel(const DescriptorBindingModel &other) noexcept = default;
    DescriptorBindingModel(DescriptorBindingModel &&other) noexcept = default;
    DescriptorBindingModel &operator=(const DescriptorBindingModel &other) noexcept = default;
    DescriptorBindingModel &operator=(DescriptorBindingModel &&other) noexcept = default;

};
