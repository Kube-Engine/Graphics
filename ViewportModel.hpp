/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: ViewportModel
 */

#pragma once

#include "Vulkan.hpp"

namespace kF::Graphics
{
    struct ViewportModel;
};

/** @brief Describe how to create a sampler */
struct kF::Graphics::ViewportModel : public VkPipelineViewportStateCreateInfo
{
    /** @brief Initialize constructor */
    ViewportModel(const Viewport * const viewportBegin, const Viewport * const viewportEnd,
        const Rect2D * const scissorBegin, const Rect2D * const scissorEnd)
        noexcept
        : VkPipelineViewportStateCreateInfo {
            sType: VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
            pNext: nullptr,
            flags: ToFlags(ViewportCreateFlags::None),
            viewportCount: static_cast<std::uint32_t>(std::distance(viewportBegin, viewportEnd)),
            pViewports: viewportBegin,
            scissorCount: static_cast<std::uint32_t>(std::distance(scissorBegin, scissorEnd)),
            pScissors: scissorBegin
        } {}

    /** @brief POD semantics */
    ViewportModel(const ViewportModel &other) noexcept = default;
    ViewportModel(ViewportModel &&other) noexcept = default;
    ViewportModel &operator=(const ViewportModel &other) noexcept = default;
    ViewportModel &operator=(ViewportModel &&other) noexcept = default;
};
