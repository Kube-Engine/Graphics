/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: FrameBuffer instruction model
 */

#pragma once

#include "Vulkan.hpp"

namespace kF::Graphics
{
    struct FrameBufferModel;
}

/** @brief Describe how to create a frame buffer */
struct kF::Graphics::FrameBufferModel : public VkBufferCreateInfo
{
    /** @brief Initialize constructor */
    FrameBufferModel(const FramebufferCreateFlags flags_, const RenderPassHandle renderPass_,
            const ImageViewHandle* attachmentBegin, const ImageViewHandle* attachmentEnd,
            const std::uint32_t width_, const std::uint32_t height_, const std::uint32_t layers_)
        noexcept
        : VkFramebufferCreateInfo(
            sType: VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
            pNext: nullptr,
            flags: flags_,
            renderPass: renderPass_,
            attachmentCount: std::distance(attachmentBegin, attachmentEnd),
            pAttachments: attachmentBegin,
            width: width_,
            height: height_,
            layers: layers_
        ) {}

    /** @brief POD semantics */
    FrameBufferModel(const FrameBufferModel &other) noexcept = default;
    FrameBufferModel(FrameBufferModel &&other) noexcept = default;
    FrameBufferModel &operator=(const FrameBufferModel &other) noexcept = default;
    FrameBufferModel &operator=(FrameBufferModel &&other) noexcept = default;
};