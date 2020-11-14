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
class alignas_cacheline kF::Graphics::FramebufferManager final : public CachedRendererObject
{
public:
    /** @brief Construct a framebuffer handler */
    FramebufferManager(void);

    /** @brief Move constructor */
    FramebufferManager(FramebufferManager &&other) noexcept = default;

    /** @brief Destoy the handler */
    ~FramebufferManager(void) noexcept = default;

    /** @brief Move assignment */
    FramebufferManager &operator=(FramebufferManager &&other) noexcept = default;


    /** @brief Get the framebuffer list */
    [[nodiscard]] auto &framebuffers(void) noexcept { return _cachedFrames.caches(); }
    [[nodiscard]] const auto &framebuffers(void) const noexcept { return _cachedFrames.caches(); }

    /** @brief Retreive the current frame buffer */
    [[nodiscard]] FramebufferHandle currentFramebuffer(void) const noexcept { return _cachedFrames.currentCache(); }


    /** @brief Callback triggered when renderer is processing a new frame */
    void onFrameAquired(const FrameIndex frameIndex) noexcept;

    /** @brief Callback on render view size changed */
    void onViewSizeChanged(void);

private:
    PerFrameCache<Framebuffer> _cachedFrames {};

    /** @brief Create a set of framebuffer */
    void createFramebuffers(void);
};

static_assert_fit_cacheline(kF::Graphics::FramebufferManager);

#include "FramebufferManager.ipp"