/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: PerFrameCache
 */

#pragma once

#include <Kube/Core/Assert.hpp>
#include <Kube/Core/Vector.hpp>

namespace kF::Graphics
{
    template<typename Type>
    class PerFrameCache;

    /** @brief Index of a frame */
    using FrameIndex = std::size_t;
}

template<typename Type>
class KF_ALIGN_HALF_CACHELINE kF::Graphics::PerFrameCache
{
public:
    using CachedFrames = Core::Vector<Type>;

    /** @brief Construct the cache with a given frame count */
    PerFrameCache(const std::size_t count) noexcept : _caches(count) {}

    /** @brief Move constructor */
    PerFrameCache(PerFrameCache &&other) noexcept = default;

    /** @brief Destructor */
    ~PerFrameCache(void) noexcept_destructible(CachedFrames) = default;

    /** @brief Move assignment */
    PerFrameCache &operator=(PerFrameCache &&other) noexcept_move_assignable(CachedFrames) = default;

    /** @brief Swap two instances */
    void swap(PerFrameCache &other) noexcept
        { _caches.swap(other._caches); std::swap(_currentFrame, other._currentFrame); }

    /** @brief Get / Set the current frame */
    [[nodiscard]] FrameIndex currentFrame(void) const noexcept { return _currentFrame; }
    void setCurrentFrame(const FrameIndex frameIndex) noexcept { _currentFrame = frameIndex; }

    /** @brief Set the current frame to the next one */
    void incrementFrame(void) noexcept { _currentFrame = (_currentFrame + 1) % _caches.size(); }


    /** @brief Get the internal cache list */
    [[nodiscard]] auto &caches(void) noexcept { return _caches; }
    [[nodiscard]] const auto caches(void) const noexcept { return _caches; }

    /** @brief Get the cache at given index */
    [[nodiscard]] Type &cacheAt(const std::size_t index) noexcept { return _caches[index]; }
    [[nodiscard]] const Type &cacheAt(const std::size_t index) const noexcept { return _caches[index]; }

    /** @brief Get the current cache */
    [[nodiscard]] Type &currentCache(void) noexcept { return getCache(currentFrame()); }
    [[nodiscard]] const Type &currentCache(void) const noexcept { return getCache(currentFrame()); }


    /** @brief Resize the number of cache */
    void resize(const std::size_t count) noexcept_invocable(&CachedFrames::resize, std::size_t) { _caches.resize(count); }

private:
    CachedFrames _caches {};
    FrameIndex _currentFrame { 0u };

};

static_assert(sizeof(kF::Graphics::PerFrameCache<char>) == kF::Core::CacheLineHalfSize, "PerFrameCache must take the half of a cacheline");
static_assert(sizeof(kF::Graphics::PerFrameCache<char[64]>) == kF::Core::CacheLineHalfSize, "PerFrameCache must take the half of a cacheline");