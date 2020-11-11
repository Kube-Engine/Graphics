/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Buffer
 */

#pragma once

#include "BufferModel.hpp"
#include "VulkanHandle.hpp"

namespace kF::Graphics
{
    class Buffer;
}

/** @brief GPU Memory buffer abstraction */
class kF::Graphics::Buffer final : public VulkanHandle<BufferHandle>
{
public:
    /** @brief Construct a nw buffer using a buffer model */
    Buffer(Renderer &renderer, const BufferModel &model) : VulkanHandle<BufferHandle>()
        { createBuffer(model); }

    /** @brief Move constructor */
    Buffer(Buffer &&other) noexcept = default;

    /** @brief Destruct the buffer */
    ~Buffer(void) noexcept;

    /** @brief Move assignment */
    Buffer &operator=(Buffer &&other) noexcept = default;

private:
    /** @brief Create the device buffer */
    void createBuffer(const BufferModel &model);
};