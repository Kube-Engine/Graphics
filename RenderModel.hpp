/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Render instruction model
 */

#pragma once

#include "BufferModel.hpp"

namespace kF::Graphics
{
    struct RenderModel;
}

/** @brief Describes a rendered model */
struct kF::Graphics::RenderModel
{
    PipelineIndex pipeline {};
    std::uint32_t vertexCount { 0 };
    std::uint32_t instanceCount { 0 };
    std::uint32_t vertexOffset { 0 };
    std::uint32_t instanceOffset { 0 };
    BufferIndexes buffers {};
    BufferOffsets offsets {};
};

static_assert(sizeof(kF::Graphics::RenderModel) == 40ul, "The renderer model must take 32 bytes");