/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Render instruction model
 */

#pragma once

#include "BufferModel.hpp"

namespace kF::Graphics
{
    struct RenderModel;

    /** @brief Offset in a buffer */
    using BufferOffset = VkDeviceSize;

    /** @brief A list of offsets */
    using BufferOffsets = std::vector<BufferOffset>;
}

/** @brief Describes a rendered model */
struct kF::Graphics::RenderModel
{
    std::uint32_t vertexCount { 0 };
    std::uint32_t instanceCount { 0 };
    std::uint32_t vertexOffset { 0 };
    std::uint32_t instanceOffset { 0 };
    BufferIndexes buffers {};
    BufferOffsets offsets {};
};