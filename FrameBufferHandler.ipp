/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: FrameBufferHandler
 */

inline void kF::Graphics::FrameBufferHandler::swap(FramebufferHandler &other) noexcept
{
    RendererObject::swap(other);
    std::swap(_framebuffers, other._framebuffers);
}
