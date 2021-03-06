/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: ShaderStageModel
 */

#pragma once

#include "Vulkan.hpp"

namespace kF::Graphics
{
    struct ShaderStageModel;
};

/** @brief Describe how to create a sampler */
struct kF::Graphics::ShaderStageModel : public VkPipelineShaderStageCreateInfo
{
    /** @brief Initialize constructor */
    ShaderStageModel(const ShaderStageFlags stage_, const ShaderModuleHandle module_,
            const char * const pName_ = "main", const ShaderSpecializationTable * const pSpecializationInfo_ = nullptr)
        noexcept
        : VkPipelineShaderStageCreateInfo {
            sType: VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            pNext: nullptr,
            flags: ToFlags(ShaderStageCreateFlags::None),
            stage: static_cast<VkShaderStageFlagBits>(stage_),
            module: module_,
            pName: pName_,
            pSpecializationInfo: pSpecializationInfo_
        } {}

    /** @brief POD semantics */
    ShaderStageModel(const ShaderStageModel &other) noexcept = default;
    ShaderStageModel(ShaderStageModel &&other) noexcept = default;
    ShaderStageModel &operator=(const ShaderStageModel &other) noexcept = default;
    ShaderStageModel &operator=(ShaderStageModel &&other) noexcept = default;
};
