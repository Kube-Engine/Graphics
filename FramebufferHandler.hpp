/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: FramebufferHandler
 */

#pragma once

#include "RendererObject.hpp"

namespace kF::Graphics
{
    class FramebufferHandler;

    using Framebuffer = VkFramebuffer;
    using Framebuffers = std::vector<VkFramebuffer>;
}

/** @brief A framebuffer handler holds a set of framebuffers */
class kF::Graphics::FramebufferHandler final : public RendererObject
{
public:
    /** @brief Construct a framebuffer handler */
    FramebufferHandler(Renderer &renderer);

    /** @brief Move constructor */
    FramebufferHandler(FramebufferHandler &&other) noexcept = default;

    /** @brief Destoy the handler */
    ~FramebufferHandler(void);

    /** @brief Move assignment */
    FramebufferHandler &operator=(FramebufferHandler &&other) noexcept { swap(other); return *this; };

    /** @brief Get the framebuffer list */
    [[nodiscard]] Framebuffers &getFramebuffers(void) noexcept { return _framebuffers; }
    [[nodiscard]] const Framebuffers &getFramebuffers(void) const noexcept { return _framebuffers; }

    /** @brief Swap two instances */
    void swap(FramebufferHandler &other) noexcept { std::swap(_framebuffers, other._framebuffers); }

private:
    Framebuffers _framebuffers;

    /** @brief Create a set of framebuffer */
    void createFramebuffers(void);
};