/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Pool of command buffers
 */

#pragma once

#include "Buffer.hpp"

namespace kF::Graphics
{
    class BufferPool;

    using BufferIndexes = Core::Vector<BufferIndex>;
}

/** @brief Abstract a pool of GPU buffers */
class kF::Graphics::BufferPool final : public RendererObject
{
public:
    /** @brief A pair of buffer index and its instance */
    using BufferPair = std::pair<BufferIndex, std::unique_ptr<Buffer>>;

    /** @brief A map of buffer pair */
    using BufferMap = std::vector<BufferPair>;

    /** @brief Construct a pool of buffers */
    BufferPool(Renderer &renderer) : RendererObject(renderer) {}

    /** @brief Move constructor */
    BufferPool(BufferPool &&other) noexcept = default;

    /** @brief Destruct the pool of buffers */
    ~BufferPool(void) = default;

    /** @brief Move assignment */
    BufferPool &operator=(BufferPool &&other) noexcept = default;

    /** @brief Add a buffer into the pool using a buffer model
     *  @return The index of the buffer in the pool */
    [[nodiscard]] BufferIndex addBuffer(const BufferModel &model);

    /** @brief Remove a buffer of the pool using it's index */
    void removeBuffer(const BufferIndex index);

    /** @brief Collect a list of buffers in the pool matching given indexes */
    [[nodiscard]] BufferHandles collectBuffers(const BufferIndexes &indexes);

private:
    BufferMap _bufferMap;

    /** @brief Find a buffer in the pool using its index */
    [[nodiscard]] auto findBuffer(const BufferIndex index) noexcept { return std::find_if(_bufferMap.begin(), _bufferMap.end(), [index](const auto &pair) { return pair.first == index; }); }
    [[nodiscard]] auto findBuffer(const BufferIndex index) const noexcept { return std::find_if(_bufferMap.begin(), _bufferMap.end(), [index](const auto &pair) { return pair.first == index; }); }
};




