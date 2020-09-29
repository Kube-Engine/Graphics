/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Render instruction model
 */

#pragma once

#include "BufferModel.hpp"

namespace kF
{
    struct RenderModel;

    using BufferOffset = VkDeviceSize;
    using BufferOffsets = std::vector<BufferOffset>;
}

struct kF::RenderModel
{
    std::uint32_t vertexCount { 0 };
    std::uint32_t instanceCount { 0 };
    std::uint32_t vertexOffset { 0 };
    std::uint32_t instanceOffset { 0 };
    BufferIndexes buffers {};
    BufferOffsets offsets {};
};