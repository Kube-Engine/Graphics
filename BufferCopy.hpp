/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Buffer Copy
 */

#pragma once

#include <Kube/Core/Assert.hpp>

#include "Vulkan.hpp"

namespace kF::Graphics
{
    struct BufferCopy;
};

/** @brief Describe how to create a sampler */
struct kF::Graphics::BufferCopy : public VkBufferCopy
{
    /** @brief Initialize constructor */
    BufferCopy(const BufferSize size_, const BufferSize srcOffset_ = 0u, const BufferSize dstOffset_ = 0u)
        noexcept
        : VkBufferCopy {
            srcOffset: srcOffset_,
            dstOffset: dstOffset_,
            size: size_
        } {}

    /** @brief POD semantics */
    BufferCopy(const BufferCopy &other) noexcept = default;
    BufferCopy(BufferCopy &&other) noexcept = default;
    BufferCopy &operator=(const BufferCopy &other) noexcept = default;
    BufferCopy &operator=(BufferCopy &&other) noexcept = default;
};
