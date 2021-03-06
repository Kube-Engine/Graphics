/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Framebuffer instruction model
 */

#pragma once

#include "Vulkan.hpp"

namespace kF::Graphics
{
    struct FramebufferModel;
}

/** @brief Describe how to create a frame buffer */
struct kF::Graphics::FramebufferModel : public VkFramebufferCreateInfo
{
    /** @brief Initialize constructor */
    FramebufferModel(const FramebufferCreateFlags flags_, const RenderPassHandle renderPass_,
            const ImageViewHandle* attachmentBegin, const ImageViewHandle* attachmentEnd,
            const std::uint32_t width_, const std::uint32_t height_, const std::uint32_t layers_)
        noexcept
        : VkFramebufferCreateInfo {
            sType: VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
            pNext: nullptr,
            flags: ToFlags(flags_),
            renderPass: renderPass_,
            attachmentCount: static_cast<std::uint32_t>(std::distance(attachmentBegin, attachmentEnd)),
            pAttachments: attachmentBegin,
            width: width_,
            height: height_,
            layers: layers_
        } {}

    /** @brief POD semantics */
    FramebufferModel(const FramebufferModel &other) noexcept = default;
    FramebufferModel(FramebufferModel &&other) noexcept = default;
    FramebufferModel &operator=(const FramebufferModel &other) noexcept = default;
    FramebufferModel &operator=(FramebufferModel &&other) noexcept = default;
};