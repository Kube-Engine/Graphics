/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: FrameBufferManager
 */

inline void kF::Graphics::FrameBufferManager::swap(FrameBufferManager &other) noexcept
{
    RendererObject::swap(other);
    std::swap(_cachedFrames, other._cachedFrames);
}

inline void kF::Graphics::FrameBufferManager::acquireNextFrame(void) noexcept;
{
    _cachedFrame.incrementFrame();
}

inline void kF::Graphics::FrameBufferManager::releaseFrame(const FrameIndex) noexcept
{

}