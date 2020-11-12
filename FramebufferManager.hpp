/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: FramebufferManager
 */

#pragma once

#include "PerFrameCache.hpp"
#include "Framebuffer.hpp"

namespace kF::Graphics
{
    class FramebufferManager;
}

/** @brief A framebuffer handler holds a set of framebuffers */
class alignas_cacheline kF::Graphics::FramebufferManager final : public RendererObject
{
public:
    /** @brief Construct a framebuffer handler */
    FramebufferManager(Renderer &renderer);

    /** @brief Move constructor */
    FramebufferManager(FramebufferManager &&other) noexcept = default;

    /** @brief Destoy the handler */
    ~FramebufferManager(void) noexcept = default;

    /** @brief Move assignment */
    FramebufferManager &operator=(FramebufferManager &&other) noexcept { swap(other); return *this; };

    /** @brief Swap two instances */
    void swap(FramebufferManager &other) noexcept;


    /** @brief Get the framebuffer list */
    [[nodiscard]] auto &framebuffers(void) noexcept { return _cachedFrames.caches(); }
    [[nodiscard]] const auto &framebuffers(void) const noexcept { return _cachedFrames.caches(); }

    /** @brief Retreive the current frame buffer */
    [[nodiscard]] FramebufferHandle currentFramebuffer(void) const noexcept { return _cachedFrames.currentCache(); }


    /** @brief Acquire the next frame without releasing current one */
    void acquireNextFrame(void) noexcept;

    /** @brief Release a given frame */
    void releaseFrame(const FrameIndex frameIndex) noexcept;


    /** @brief Callback on render view size changed */
    void onViewSizeChanged(void);

private:
    PerFrameCache<Framebuffer> _cachedFrames;

    /** @brief Create a set of framebuffer */
    void createFramebuffers(void);
};

static_assert_fit_cacheline(kF::Graphics::FramebufferManager);

#include "FramebufferManager.ipp"