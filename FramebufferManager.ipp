/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: FramebufferManager
 */

inline void kF::Graphics::FramebufferManager::swap(FramebufferManager &other) noexcept
{
    RendererObject::swap(other);
    _cachedFrames.swap(other._cachedFrames);
}

inline void kF::Graphics::FramebufferManager::acquireNextFrame(void) noexcept
{
    _cachedFrames.incrementFrame();
}

inline void kF::Graphics::FramebufferManager::releaseFrame(const FrameIndex) noexcept
{

}