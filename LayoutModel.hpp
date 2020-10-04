/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Layout instruction model
 */

#pragma once

#include <Kube/Core/Core.hpp>

#include "Vulkan.hpp"

namespace kF::Graphics
{
    struct LayoutModel;

    /** @brief Vulkan layout binding description */
    using LayoutBinding = VkVertexInputBindingDescription;

    /** @brief List of layout bindings */
    using LayoutBindings = std::vector<LayoutBinding>;

    /** @brief Vulkan layout attribute description */
    using LayoutAttribute = VkVertexInputAttributeDescription;

    /** @brief A list of layout attributes */
    using LayoutAttributes = std::vector<LayoutAttribute>;
}

/** @brief Model describing a memory layout of a pipeline */
struct kF::Graphics::LayoutModel
{
    LayoutBindings bindings;
    LayoutAttributes attributes;
};