/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Pool of command buffers
 */

#pragma once

#include "Buffer.hpp"

namespace kF
{
    class BufferPool;
}

class kF::BufferPool final : public RendererObject
{
public:
    using BufferPair = std::pair<BufferIndex, std::unique_ptr<Buffer>>;
    using BufferMap = std::vector<BufferPair>;

    BufferPool(Renderer &renderer);
    ~BufferPool(void);

    BufferPool &operator=(BufferPool &&other) = default;

    [[nodiscard]] BufferIndex addBuffer(const BufferModel &model);
    void removeBuffer(const BufferIndex index);

    std::vector<DeviceBuffer> collectBuffers(const BufferIndexes &indexes);

private:
    BufferMap _bufferMap;

    auto findBuffer(const BufferIndex index) noexcept { return std::find_if(_bufferMap.begin(), _bufferMap.end(), [index](const auto &pair) { return pair.first == index; }); }
    auto findBuffer(const BufferIndex index) const noexcept { return std::find_if(_bufferMap.begin(), _bufferMap.end(), [index](const auto &pair) { return pair.first == index; }); }
};




