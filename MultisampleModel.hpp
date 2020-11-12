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
    MultisampleModel(const MultisampleCreateFlags flags_, const SampleCountFlags rasterizationSamples_,
            const bool sampleShadingEnable_, const float minSampleShading_, const SampleMask * const pSampleMask_,
            const bool alphaToCoverageEnable_, const bool alphaToOneEnable_)
        noexcept
        : VkPipelineMultisampleStateCreateInfo {
            sType: VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
            pNext: nullptr,
            flags: ToFlags(flags_),
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
