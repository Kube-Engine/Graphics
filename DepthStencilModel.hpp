/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: DepthStencilModel
 */

#pragma once

#include "Vulkan.hpp"

namespace kF::Graphics
{
    struct DepthStencilModel;
};

/** @brief Describe how to create a sampler */
struct kF::Graphics::DepthStencilModel : public VkPipelineDepthStencilStateCreateInfo
{
    /** @brief Initialize constructor */
    DepthStencilModel(const DepthStencilCreateFlags flags_, const bool depthTestEnable_, const bool depthWriteEnable_,
            const CompareOp depthCompareOp_, const bool depthBoundsTestEnable_, const bool stencilTestEnable_,
            const StencilOpState front_, const StencilOpState back_, const float minDepthBounds_, const float maxDepthBounds_)
        noexcept
        : VkPipelineDepthStencilStateCreateInfo {
            sType: VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
            pNext: nullptr,
            flags: ToFlags(flags_),
            depthTestEnable: depthTestEnable_,
            depthWriteEnable: depthWriteEnable_,
            depthCompareOp: static_cast<VkCompareOp>(depthCompareOp_),
            depthBoundsTestEnable: depthBoundsTestEnable_,
            stencilTestEnable: stencilTestEnable_,
            front: front_,
            back: back_,
            minDepthBounds: minDepthBounds_,
            maxDepthBounds: maxDepthBounds_
        } {}

    /** @brief POD semantics */
    DepthStencilModel(const DepthStencilModel &other) noexcept = default;
    DepthStencilModel(DepthStencilModel &&other) noexcept = default;
    DepthStencilModel &operator=(const DepthStencilModel &other) noexcept = default;
    DepthStencilModel &operator=(DepthStencilModel &&other) noexcept = default;
};
