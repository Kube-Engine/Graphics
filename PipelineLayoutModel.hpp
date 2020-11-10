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
struct alignas_half_cacheline kF::Graphics::PipelineLayoutModel
{
    VertexInputBindings bindings;
    VertexInputAttributes attributes;
};

static_assert_fit_half_cacheline(kF::Graphics::PipelineLayoutModel);
