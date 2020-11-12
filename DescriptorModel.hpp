/**
 * @ Author: Pierre Veysseyre
 * @ Description: UniformModel.hpp
 */

#pragma once

#include "Vulkan.hpp"
#include "DescriptorBindingModel.hpp"

namespace kF::Graphics
{
    struct DescriptorModel;
};


// VkDescriptorSetLayoutBinding (layoutBinding) -> binding -> descriptorType -> descriptorCount -> stageFlags -> pImmutableSamplers
// VkDescriptorSetLayoutCreateInfo -> bindingCount -> pBindings=layoutBinding

/** @brief Describe how to create an image */
struct kF::Graphics::DescriptorModel : public VkDescriptorSetLayoutCreateInfo
{
    /** @brief Make a unique (one descriptor) Uniform Buffer Descriptor */
    [[nodiscard]] static DescriptorModel MakeUniqueUniformBuffer(const uint32_t binding, const ShaderStageFlags shaderStage) noexcept;

    /** @brief Initialize constructor */
    DescriptorModel(const DescriptorSetLayoutCreateFlags flags_, const DescriptorBindingModels &bindings_)
        noexcept
        : VkDescriptorSetLayoutCreateInfo {
            sType: VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
            pNext: nullptr,
            flags: ToFlags(flags_),
            bindingCount: static_cast<uint32_t>(bindings_.size()),
            pBindings: static_cast<VkDescriptorSetLayoutBinding *>(bindings_.data())
         } {}


    /** @brief POD semantics */
    DescriptorModel(const DescriptorModel &other) noexcept = default;
    DescriptorModel(DescriptorModel &&other) noexcept = default;
    DescriptorModel &operator=(const DescriptorModel &other) noexcept = default;
    DescriptorModel &operator=(DescriptorModel &&other) noexcept = default;

};

#include "DescriptorModel.ipp"