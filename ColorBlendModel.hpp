/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: ColorBlendModel
 */

#pragma once

#include "ColorBlendAttachement.hpp"

namespace kF::Graphics
{
    struct ColorBlendModel;
};

/** @brief Describe how to create a sampler */
struct kF::Graphics::ColorBlendModel : public VkPipelineColorBlendStateCreateInfo
{
    /** @brief Initialize constructor */
    ColorBlendModel(const bool logicOpEnable_, const LogicOp logicOp_,
            const ColorBlendAttachment * const attachmentBegin, const ColorBlendAttachment * const attachmentEnd,
            const float blendRed = 0.0f, const float blendGreen = 0.0f, const float blendBlue = 0.0f, const float blendAlpha = 0.0f)
        noexcept
        : VkPipelineColorBlendStateCreateInfo {
            sType: VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
            pNext: nullptr,
            flags: ToFlags(ColorBlendCreateFlags::None),
            logicOpEnable: logicOpEnable_,
            logicOp: static_cast<VkLogicOp>(logicOp_),
            attachmentCount: static_cast<std::uint32_t>(std::distance(attachmentBegin, attachmentEnd)),
            pAttachments: attachmentBegin,
            blendConstants: {
                blendRed, blendGreen, blendBlue, blendAlpha
            }
        } {}

    /** @brief POD semantics */
    ColorBlendModel(const ColorBlendModel &other) noexcept = default;
    ColorBlendModel(ColorBlendModel &&other) noexcept = default;
    ColorBlendModel &operator=(const ColorBlendModel &other) noexcept = default;
    ColorBlendModel &operator=(ColorBlendModel &&other) noexcept = default;
};
