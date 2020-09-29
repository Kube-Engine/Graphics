/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: FramebufferHandler
 */

#pragma once

#include "RendererObject.hpp"

namespace kF
{
    class FramebufferHandler;

    using Framebuffer = VkFramebuffer;
    using Framebuffers = std::vector<VkFramebuffer>;
}

class kF::FramebufferHandler final : public RendererObject
{
public:
    FramebufferHandler(Renderer &renderer);
    FramebufferHandler(FramebufferHandler &&other) = default;
    virtual ~FramebufferHandler(void);

    FramebufferHandler &operator=(FramebufferHandler &&other) { swap(other); return *this; };

    [[nodiscard]] Framebuffers &getFramebuffers(void) noexcept { return _framebuffers; }
    [[nodiscard]] const Framebuffers &getFramebuffers(void) const noexcept { return _framebuffers; }

    void swap(FramebufferHandler &other) { std::swap(_framebuffers, other._framebuffers); }

private:
    Framebuffers _framebuffers;

    void createFramebuffers(void);
};