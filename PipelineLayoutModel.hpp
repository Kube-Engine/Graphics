/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Layout instruction model
 */

#pragma once

#include <Kube/Core/Vector.hpp>

#include "Vulkan.hpp"

namespace kF::Graphics
{
    struct PipelineLayoutModel;

    /** @brief Vulkan layout binding description */
    using VertexInputBinding = VkVertexInputBindingDescription;

    /** @brief List of layout bindings */
    using VertexInputBindings = Core::TinyVector<VertexInputBinding>;

    /** @brief Vulkan layout attribute description */
    using VertexInputAttribute = VkVertexInputAttributeDescription;

    /** @brief A list of layout attributes */
    using VertexInputAttributes = Core::TinyVector<LayoutAttribute>;
}

/** @brief Model describing a memory layout of a pipeline */
struct KF_ALIGN_HALF_CACHELINE kF::Graphics::PipelineLayoutModel
{
    VertexInputBindings bindings;
    VertexInputAttributes attributes;
};

static_assert(sizeof(kF::Graphics::PipelineLayoutModel) == kF::Core::CacheLineHalfSize, "PipelineLayoutModel must take the half of a cacheline");
static_assert(alignof(kF::Graphics::PipelineLayoutModel) == kF::Core::CacheLineHalfSize, "PipelineLayoutModel must be aligned to the half of a cacheline");