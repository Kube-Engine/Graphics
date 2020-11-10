/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: CommandModel
 */

#pragma once

#include <variant>

#include <Kube/Core/Vector.hpp>

#include "Buffer.hpp"
#include "FrameBuffer.hpp"
#include "Pipeline.hpp"

namespace kF::Graphics
{
    struct RenderModel;
    struct TransferModel;

    /** @brief CommandModel is a concept that match all types of command models */
    template<typename Type>
    concept CommandModel = std::is_same_v<Type, RenderModel> || std::is_same_v<Type, TransferModel>;
}

/** @brief Model of a render command buffer */
struct alignas_cacheline kF::Graphics::RenderModel
{
    FrameBufferHandle frameBuffer { NullHandle };
    PipelineHandle pipeline { NullHandle };
    std::uint32_t vertexCount { 0u };
    std::uint32_t vertexOffset { 0u };
    std::uint32_t instanceCount { 0u };
    std::uint32_t instanceOffset { 0u };
    Core::TinyVector<BufferHandle> buffers {};
    Core::TinyVector<BufferOffset> bufferOffsets {};
};

static_assert_fit_cacheline(kF::Graphics::RenderModel);

/** @brief Model of a transfer command buffer */
struct alignas_cacheline kF::Graphics::TransferModel
{
    BufferHandle source { NullHandle };
    BufferHandle destination { NullHandle };
    BufferSize size { 0u };
    BufferOffset offset { 0u };
    BufferOffset destinationOffset { 0u };
};
static_assert_fit_cacheline(kF::Graphics::TransferModel);