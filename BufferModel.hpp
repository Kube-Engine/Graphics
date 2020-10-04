/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Buffer model
 */

#pragma once

#include <cinttypes>
#include <vector>
#include <concepts>

namespace kF::Graphics
{
    struct BufferModel;

    /** @brief Index of a buffer in the pool */
    using BufferIndex = std::uint32_t;

    /** @brief A list of buffer indexes */
    using BufferIndexes = std::vector<BufferIndex>;
}

/** @brief A buffer model describes a buffer that should be copied to GPU memory */
struct kF::Graphics::BufferModel
{
    const void *data { nullptr }; // Opaque data pointer
    std::size_t size { 0u }; // Data size in bytes

    /** @brief Construct a buffer model from a container */
    template<typename Container>
    static BufferModel FromContainer(const Container &other) noexcept
    {
        using StoredType = decltype(*other.data());

        return BufferModel {
            data: other.data(),
            size: other.size() * sizeof(StoredType)
        };
    }

    /** @brief Construct a buffer model from iterators */
    template<std::forward_iterator ForwardIterator>
    static BufferModel FromIterators(const ForwardIterator from, const ForwardIterator to) noexcept
    {
        using StoredType = decltype(*from);

        return BufferModel {
            data: from,
            size: std::distance(from, to) * sizeof(StoredType)
        };
    }
};