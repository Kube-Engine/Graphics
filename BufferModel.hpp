/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Buffer model
 */

#pragma once

#include <cinttypes>
#include <vector>
#include <concepts>

#include <Kube/Core/FlatVector.hpp>

namespace kF::Graphics
{
    struct BufferModel;

    /** @brief Index of a buffer in the pool */
    using BufferIndex = std::uint32_t;

    /** @brief Size of a buffer */
    using BufferSize = VkDeviceSize;

    /** @brief Offset in a buffer */
    using BufferOffset = VkDeviceSize;
}

/** @brief A buffer model describes a buffer that should be copied to GPU memory */
struct kF::Graphics::BufferModel
{
    /** @brief Different locations of memory */
    enum class Location : std::uint32_t {
        Local,
        Shared
    };

    /** @brief Different types of usages */
    enum class Usage : std::uint32_t {
        Transfer,
        Vertex,
        Index
    };

    const void *data { nullptr }; // Opaque data pointer
    std::size_t size { 0ul }; // Data size in bytes
    Location location { Location::Local }; // Location of the buffer memory
    Usage usage { Usage::Transfer }; // Usage of the buffer

    /** @brief Construct a buffer model from a container */
    template<typename Container>
    static BufferModel FromContainer(const Container &other, const Location location, const Usage usage) noexcept
    {
        using StoredType = decltype(*other.data());

        return BufferModel {
            data: other.data(),
            size: other.size() * sizeof(StoredType),
            location: location,
            usage: usage
        };
    }

    /** @brief Construct a buffer model from iterators */
    template<std::forward_iterator ForwardIterator>
    static BufferModel FromIterators(const ForwardIterator from, const ForwardIterator to, const Location location, const Usage usage) noexcept
    {
        using StoredType = decltype(*from);

        return BufferModel {
            data: from,
            size: std::distance(from, to) * sizeof(StoredType),
            location: location,
            usage: usage
        };
    }
};