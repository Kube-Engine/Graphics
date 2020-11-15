/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: VertexInputBinding
 */

#pragma once

#include "Vulkan.hpp"

namespace kF::Graphics
{
    struct VertexInputBinding;
};

/** @brief Describe how to create a sampler */
struct kF::Graphics::VertexInputBinding : public VkVertexInputBindingDescription
{
    /** @brief Initialize constructor */
    VertexInputBinding(const std::uint32_t binding_, const std::uint32_t stride_, const VertexInputRate inputRate_)
        noexcept
        : VkVertexInputBindingDescription {
            binding: binding_,
            stride: stride_,
            inputRate: static_cast<VkVertexInputRate>(inputRate_),
        } {}

    /** @brief POD semantics */
    VertexInputBinding(const VertexInputBinding &other) noexcept = default;
    VertexInputBinding(VertexInputBinding &&other) noexcept = default;
    VertexInputBinding &operator=(const VertexInputBinding &other) noexcept = default;
    VertexInputBinding &operator=(VertexInputBinding &&other) noexcept = default;
};
