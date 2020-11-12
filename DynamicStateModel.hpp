/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: DynamicStateModel
 */

#pragma once

#include "Vulkan.hpp"

namespace kF::Graphics
{
    struct DynamicStateModel;
};

/** @brief Describe how to create a sampler */
struct kF::Graphics::DynamicStateModel : public VkPipelineDynamicStateCreateInfo
{
    /** @brief Initialize constructor */
    DynamicStateModel(const DynamicStateCreateFlags flags_, const DynamicState * const stateBegin, const DynamicState * const stateEnd)
        noexcept
        : VkPipelineDynamicStateCreateInfo {
            sType: VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
            pNext: nullptr,
            flags: ToFlags(flags_),
            dynamicStateCount: static_cast<std::uint32_t>(std::distance(stateBegin, stateEnd)),
            pDynamicStates: reinterpret_cast<const VkDynamicState * const>(stateBegin)
        } {}

    /** @brief POD semantics */
    DynamicStateModel(const DynamicStateModel &other) noexcept = default;
    DynamicStateModel(DynamicStateModel &&other) noexcept = default;
    DynamicStateModel &operator=(const DynamicStateModel &other) noexcept = default;
    DynamicStateModel &operator=(DynamicStateModel &&other) noexcept = default;
};
