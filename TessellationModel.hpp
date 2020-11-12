/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: TessellationModel
 */

#pragma once

#include "Vulkan.hpp"

namespace kF::Graphics
{
    struct TessellationModel;
};

/** @brief Describe how to create a sampler */
struct kF::Graphics::TessellationModel : public VkPipelineTessellationStateCreateInfo
{
    /** @brief Initialize constructor */
    TessellationModel(const TessellationCreateFlags flags_, const std::uint32_t patchControlPoints_)
        noexcept
        : VkPipelineTessellationStateCreateInfo {
            sType: VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO,
            pNext: nullptr,
            flags: ToFlags(flags_),
            patchControlPoints: patchControlPoints_
        } {}

    /** @brief POD semantics */
    TessellationModel(const TessellationModel &other) noexcept = default;
    TessellationModel(TessellationModel &&other) noexcept = default;
    TessellationModel &operator=(const TessellationModel &other) noexcept = default;
    TessellationModel &operator=(TessellationModel &&other) noexcept = default;
};
