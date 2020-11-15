/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: StencilOpState
 */

#pragma once

#include "Vulkan.hpp"

namespace kF::Graphics
{
    struct StencilOpState;
};

/** @brief Describe how to create a sampler */
struct kF::Graphics::StencilOpState : public VkStencilOpState
{
    /** @brief Initialize constructor */
    StencilOpState(const StencilOp failOp_ = StencilOp::Keep, const StencilOp passOp_ = StencilOp::Keep,
            const StencilOp depthFailOp_ = StencilOp::Keep, const CompareOp compareOp_ = CompareOp::Never,
            const std::uint32_t compareMask_ = 0u, const std::uint32_t writeMask_ = 0u, const std::uint32_t reference_ = 0u)
        noexcept
        : VkStencilOpState {
            failOp: static_cast<VkStencilOp>(failOp_),
            passOp: static_cast<VkStencilOp>(passOp_),
            depthFailOp: static_cast<VkStencilOp>(depthFailOp_),
            compareOp: static_cast<VkCompareOp>(compareOp_),
            compareMask: compareMask_,
            writeMask: writeMask_,
            reference: reference_
        } {}

    /** @brief POD semantics */
    StencilOpState(const StencilOpState &other) noexcept = default;
    StencilOpState(StencilOpState &&other) noexcept = default;
    StencilOpState &operator=(const StencilOpState &other) noexcept = default;
    StencilOpState &operator=(StencilOpState &&other) noexcept = default;
};
