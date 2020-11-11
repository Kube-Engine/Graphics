/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: FrameBuffer
 */

#pragma once

#include "VulkanHandle.hpp"
#include "FrameBufferModel.hpp"

namespace kF::Graphics
{
    class FrameBuffer;
}

class kF::Graphics::FrameBuffer : public VulkanHandle<FrameBufferHandle>
{
public:
    /** @brief Construct a pipeline using a model */
    FrameBuffer(Renderer &renderer, const FrameBufferModel &model)
        : VulkanHandle<FrameBufferHandle>(renderer) { createFrameBuffer(model); }

    /** @brief Move constructor */
    FrameBuffer(FrameBuffer &&other) noexcept = default;

    /** @brief Destruct the pipelineLayout */
    ~FrameBuffer(void);

    /** @brief Move assignment */
    FrameBuffer &operator=(FrameBuffer &&other) noexcept = default;

private:
    /** @brief Create a pipeline layout from model */
    void createFrameBuffer(const FrameBufferModel &model);
};