/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: VertexInputModel
 */

#pragma once

#include "Vulkan.hpp"

namespace kF::Graphics
{
    struct VertexInputModel;
};

/** @brief Describe how to create a sampler */
struct kF::Graphics::VertexInputModel : public VkPipelineVertexInputStateCreateInfo
{
    /** @brief Initialize constructor */
    VertexInputModel(const VertexInputCreateFlags flags_,
            const VertexInputBindingDescription * const bindingBegin, const VertexInputBindingDescription * const bindingEnd,
            const VertexInputAttributeDescription * const attributeBegin, const VertexInputAttributeDescription * const attributeEnd)
        noexcept
        : VkPipelineVertexInputStateCreateInfo {
            sType: VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
            pNext: nullptr,
            flags: ToFlags(flags_),
            vertexBindingDescriptionCount: static_cast<std::uint32_t>(std::distance(bindingBegin, bindingEnd)),
            pVertexBindingDescriptions: bindingBegin,
            vertexAttributeDescriptionCount: static_cast<std::uint32_t>(std::distance(attributeBegin, attributeEnd)),
            pVertexAttributeDescriptions: attributeBegin
        } {}

    /** @brief POD semantics */
    VertexInputModel(const VertexInputModel &other) noexcept = default;
    VertexInputModel(VertexInputModel &&other) noexcept = default;
    VertexInputModel &operator=(const VertexInputModel &other) noexcept = default;
    VertexInputModel &operator=(VertexInputModel &&other) noexcept = default;
};
