/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: CommandModel
 */

#pragma once

#include <variant>

#include <Kube/Core/Vector.hpp>

#include "Buffer.hpp"
#include "PipelinePool.hpp"

namespace kF::Graphics
{
    struct RenderModel;
    struct TransferModel;

    /** @brief CommandModel is a concept that match all types of command models */
    template<typename Type>
    concept CommandModel = std::is_same_v<Type, RenderModel> || std::is_same_v<Type, TransferModel>;
}

struct KF_ALIGN_CACHELINE kF::Graphics::RenderModel
{
    PipelineIndex pipeline { 0u };
    std::uint32_t vertexCount { 0u };
    std::uint32_t vertexOffset { 0u };
    std::uint32_t instanceCount { 0u };
    std::uint32_t instanceOffset { 0u };
    Core::TinyVector<BufferHandle> buffers {};
    Core::TinyVector<BufferOffset> bufferOffsets {};
};

struct KF_ALIGN_CACHELINE kF::Graphics::TransferModel
{
    BufferHandle source { NullHandle };
    BufferHandle destination { NullHandle };
    BufferSize size { 0u };
    BufferOffset offset { 0u };
    BufferOffset destinationOffset { 0u };
};