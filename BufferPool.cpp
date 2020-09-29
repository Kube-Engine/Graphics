/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Pool of command buffer objects
 */

#include "Renderer.hpp"

using namespace kF;

BufferPool::BufferPool(Renderer &renderer) : RendererObject(renderer)
{
}

BufferPool::~BufferPool(void)
{
}

BufferIndex BufferPool::addBuffer(const BufferModel &model)
{
    auto index = 1u;

    if (!_bufferMap.empty())
        index = _bufferMap.back().first + 1;
    _bufferMap.emplace_back(index, std::make_unique<Buffer>(parent(), model));
    return index;
}

void BufferPool::removeBuffer(const BufferIndex index)
{
    auto it = findBuffer(index);

    if (it == _bufferMap.end())
        throw std::runtime_error("BufferPool::removeBuffer: Coudln't find buffer of index '" + std::to_string(index) + '\'');
    _bufferMap.erase(it);
}

std::vector<DeviceBuffer> BufferPool::collectBuffers(const BufferIndexes &indexes)
{
    std::vector<DeviceBuffer> buffers;
    auto count = indexes.size();

    buffers.reserve(indexes.size());
    for (auto &pair : _bufferMap) {
        for (auto index : indexes) {
            if (index != pair.first)
                continue;
            buffers.emplace_back(pair.second->getDeviceBuffer());
            if (!--count)
                break;
        }
    }
    if (count)
        throw std::runtime_error("BufferPool::collectBuffers: Could only find " + std::to_string(indexes.size() - count) + " buffers out of " + std::to_string(indexes.size()));
    return buffers;
}