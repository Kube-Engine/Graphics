/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Buffer model
 */

#pragma once

#include <cinttypes>
#include <vector>

namespace kF
{
    struct BufferModel;

    using BufferIndex = std::uint32_t;
    using BufferIndexes = std::vector<BufferIndex>;
}

struct kF::BufferModel
{
    const void *data { nullptr }; // Opaque data pointer
    std::size_t size { 0u }; // Data size in bytes

    template<typename Type>
    static BufferModel FromVector(const Type &other) {
        using StoredType = decltype(*other.data());

        return BufferModel {
            .data = other.data(),
            .size = other.size() * sizeof(StoredType)
        };
    }
};