/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: FrameBufferManager
 */

#pragma once

#include "PerFrameCache.hpp"
#include "FrameBuffer.hpp"

namespace kF::Graphics
{
    class FrameBufferManager;

    /** @brief Frame buffer handle */
    using FrameBufferHandle = VkFrameBuffer;
}

/** @brief A frameBuffer handler holds a set of frameBuffers */
class alignas_cacheline kF::Graphics::FrameBufferManager final : public RendererObject
{
public:
    /** @brief Construct a frameBuffer handler */
    FrameBufferManager(Renderer &renderer);

    /** @brief Move constructor */
    FrameBufferManager(FrameBufferManager &&other) noexcept = default;

    /** @brief Destoy the handler */
    ~FrameBufferManager(void) noexcept = default;

    /** @brief Move assignment */
    FrameBufferManager &operator=(FrameBufferManager &&other) noexcept { swap(other); return *this; };

    /** @brief Get the frameBuffer list */
    [[nodiscard]] auto &frameBuffers(void) noexcept { return _cachedFrames.caches(); }
    [[nodiscard]] const auto &frameBuffers(void) const noexcept { return _cachedFrames.caches(); }

    /** @brief Retreive the current frame buffer */
    [[nodiscard]] FrameBufferHandle currentFrameBuffer(void) const noexcept { return _cachedFrames.currentCache(); }

    /** @brief Swap two instances */
    void swap(FrameBufferManager &other) noexcept;

    /** @brief Acquire the next frame without releasing current one */
    void acquireNextFrame(void) noexcept;

    /** @brief Release a given frame */
    void releaseFrame(const FrameIndex frameIndex) noexcept;

private:
    PerFrameCache<FrameBufferHandle> _cachedFrames;

    /** @brief Create a set of frameBuffer */
    void createFrameBuffers(void);
};

static_assert_fit_cacheline(kF::Graphics::FrameBufferManager)

#include "FrameBufferManager.ipp"