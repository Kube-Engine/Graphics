/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: ColorBlendModel
 */

#pragma once

#include "Vulkan.hpp"

namespace kF::Graphics
{
    struct ColorBlendModel;
};

/** @brief Describe how to create a sampler */
struct kF::Graphics::ColorBlendModel : public VkPipelineColorBlendStateCreateInfo
{
    /** @brief Initialize constructor */
    ColorBlendModel(const ColorBlendCreateFlags flags_, const bool logicOpEnable_, const LogicOp logicOp_,
            const ColorBlendAttachmentState * const attachmentBegin, const ColorBlendAttachmentState * const atttachmentEnd,
            const float blendConstants_[4])
        noexcept
        : VkPipelineColorBlendStateCreateInfo {
            sType: VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
            pNext: nullptr,
            flags: ToFlags(flags_),
            logicOpEnable: logicOpEnable,
            logicOp: static_cast<VkLogicOp>(logicOp),
            attachmentCount: static_cast<std::uint32_t>(std::distance(attachmentBegin, attachmentEnd)),
            pAttachments: attachmentBegin,
            blendConstants: blendConstants
        } {}

    /** @brief POD semantics */
    ColorBlendModel(const ColorBlendModel &other) noexcept = default;
    ColorBlendModel(ColorBlendModel &&other) noexcept = default;
    ColorBlendModel &operator=(const ColorBlendModel &other) noexcept = default;
    ColorBlendModel &operator=(ColorBlendModel &&other) noexcept = default;
};
