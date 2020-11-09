/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Pool of command buffer objects
 */

#include "Renderer.hpp"

using namespace kF;

Graphics::BufferIndex Graphics::BufferPool::addBuffer(const BufferModel &model)
{
    auto index = 1u;

    if (!_bufferMap.empty())
        index = _bufferMap.back().first + 1;
    _bufferMap.emplace_back(index, std::make_unique<Buffer>(parent(), model));
    return index;
}

void Graphics::BufferPool::removeBuffer(const BufferIndex index)
{
    auto it = findBuffer(index);

    if (it == _bufferMap.end())
        throw std::runtime_error("Graphics::BufferPool::removeBuffer: Coudln't find buffer of index '" + std::to_string(index) + '\'');
    _bufferMap.erase(it);
}

Graphics::BufferHandles Graphics::BufferPool::collectBuffers(const BufferIndexes &indexes)
{
    std::vector<BufferHandle> buffers;
    auto count = indexes.size();

    buffers.reserve(indexes.size());
    for (auto &pair : _bufferMap) {
        for (auto index : indexes) {
            if (index != pair.first)
                continue;
            buffers.emplace_back(pair.second->handle());
            if (!--count)
                break;
        }
    }
    if (count)
        throw std::runtime_error("Graphics::BufferPool::collectBuffers: Could only find " + std::to_string(indexes.size() - count) + " buffers out of " + std::to_string(indexes.size()));
    return buffers;
}