/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: FramebufferManager
 */

inline void kF::Graphics::FramebufferManager::onFrameAquired(const FrameIndex frameIndex) noexcept
{
    _cachedFrames.setCurrentFrame(frameIndex);
}

inline void kF::Graphics::FramebufferManager::onViewSizeChanged(void)
{
    _cachedFrames.caches().clear();
    createFramebuffers();
}
