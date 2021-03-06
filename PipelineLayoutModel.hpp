/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: PipelineLayoutModel
 */

#pragma once

#include "Vulkan.hpp"

namespace kF::Graphics
{
    struct PipelineLayoutModel;
};

/** @brief Describe how to create a sampler */
struct kF::Graphics::PipelineLayoutModel : public VkPipelineLayoutCreateInfo
{
    /** @brief Initialize constructor */
    PipelineLayoutModel(const DescriptorSetLayoutHandle * const setLayoutBegin, const DescriptorSetLayoutHandle * const setLayoutEnd,
            const PushConstantRange * const pushConstantBegin, const PushConstantRange * const pushConstantEnd)
        noexcept
        : VkPipelineLayoutCreateInfo {
            sType: VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
            pNext: nullptr,
            flags: ToFlags(PipelineLayoutCreateFlags::None),
            setLayoutCount: static_cast<std::uint32_t>(std::distance(setLayoutBegin, setLayoutEnd)),
            pSetLayouts: setLayoutBegin,
            pushConstantRangeCount: static_cast<std::uint32_t>(std::distance(pushConstantBegin, pushConstantEnd)),
            pPushConstantRanges: pushConstantBegin
        } {}

    /** @brief POD semantics */
    PipelineLayoutModel(const PipelineLayoutModel &other) noexcept = default;
    PipelineLayoutModel(PipelineLayoutModel &&other) noexcept = default;
    PipelineLayoutModel &operator=(const PipelineLayoutModel &other) noexcept = default;
    PipelineLayoutModel &operator=(PipelineLayoutModel &&other) noexcept = default;
};
