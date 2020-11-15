/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: MultisampleModel
 */

#pragma once

#include "Vulkan.hpp"

namespace kF::Graphics
{
    struct MultisampleModel;
};

/** @brief Describe how to create a sampler */
struct kF::Graphics::MultisampleModel : public VkPipelineMultisampleStateCreateInfo
{
    /** @brief Initialize constructor */
    MultisampleModel(const SampleCountFlags rasterizationSamples_, const bool sampleShadingEnable_ = false,
            const float minSampleShading_ = 1.0f, const SampleMask * const pSampleMask_ = nullptr,
            const bool alphaToCoverageEnable_ = false, const bool alphaToOneEnable_ = false)
        noexcept
        : VkPipelineMultisampleStateCreateInfo {
            sType: VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
            pNext: nullptr,
            flags: ToFlags(MultisampleCreateFlags::None),
            rasterizationSamples: static_cast<VkSampleCountFlagBits>(rasterizationSamples_),
            sampleShadingEnable: sampleShadingEnable_,
            minSampleShading: minSampleShading_,
            pSampleMask: pSampleMask_,
            alphaToCoverageEnable: alphaToCoverageEnable_,
            alphaToOneEnable: alphaToOneEnable_
        } {}

    /** @brief POD semantics */
    MultisampleModel(const MultisampleModel &other) noexcept = default;
    MultisampleModel(MultisampleModel &&other) noexcept = default;
    MultisampleModel &operator=(const MultisampleModel &other) noexcept = default;
    MultisampleModel &operator=(MultisampleModel &&other) noexcept = default;
};
