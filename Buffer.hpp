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
    /** @brief Make a staging buffer */
    [[nodiscard]] static inline Buffer MakeStaging(const BufferSize size) noexcept
        { return Buffer(BufferModel::MakeStaging(size)); }

    /** @brief Make a local (GPU only) vertex buffer */
    [[nodiscard]] static inline Buffer MakeVertexLocal(const BufferSize size) noexcept
        { return Buffer(BufferModel::MakeVertexLocal(size)); }

    /** @brief Make a shared (CPU & GPU) vertex buffer */
    [[nodiscard]] static inline Buffer MakeVertexShared(const BufferSize size) noexcept
        { return Buffer(BufferModel::MakeVertexShared(size)); }

    /** @brief Make a local (GPU only) index buffer */
    [[nodiscard]] static inline Buffer MakeIndexLocal(const BufferSize size) noexcept
        { return Buffer(BufferModel::MakeIndexLocal(size)); }

    /** @brief Make a shared (CPU & GPU) index buffer */
    [[nodiscard]] static inline Buffer MakeIndexShared(const BufferSize size) noexcept
        { return Buffer(BufferModel::MakeIndexShared(size)); }


    /** @brief Construct a nw buffer using a buffer model */
    Buffer(const BufferModel &model) { createBuffer(model); }

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
