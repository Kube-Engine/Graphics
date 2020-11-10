/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: FrameBuffer
 */

#pragma once

#include "FrameBufferModel.hpp"

namespace kF::Graphics
{
    class FrameBuffer;

    /** @brief A device pipeline layout */
    using FrameBufferHandle = VkFramebuffer;
}

class kF::Graphics::FrameBuffer : public VulkanHandler<FrameBufferHandle>
{
public:
    /** @brief Construct a pipeline using a model */
    FrameBuffer(Renderer &renderer, const FrameBufferModel &model)
        : VulkanHandler<FrameBufferHandle>(renderer) { createFrameBuffer(model); }

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