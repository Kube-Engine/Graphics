/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Layout instruction model
 */

#pragma once

#include <Kube/Core/Core.hpp>

#include "Vulkan.hpp"

namespace kF
{
    struct LayoutModel;

    using LayoutBinding = VkVertexInputBindingDescription;
    using LayoutBindings = std::vector<LayoutBinding>;

    using LayoutAttribute = VkVertexInputAttributeDescription;
    using LayoutAttributes = std::vector<LayoutAttribute>;
}

struct kF::LayoutModel
{
    LayoutBindings bindings;
    LayoutAttributes attributes;
};