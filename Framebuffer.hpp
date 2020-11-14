/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Framebuffer
 */

#pragma once

#include "VulkanHandle.hpp"
#include "FramebufferModel.hpp"

namespace kF::Graphics
{
    class Framebuffer;
}

/** @brief Abstract a frame buffer */
class kF::Graphics::Framebuffer : public VulkanHandle<FramebufferHandle>
{
public:
    /** @brief Construct a pipeline using a model */
    Framebuffer(const FramebufferModel &model) { createFramebuffer(model); }

    /** @brief Move constructor */
    Framebuffer(Framebuffer &&other) noexcept = default;

    /** @brief Destruct the pipelineLayout */
    ~Framebuffer(void);

    /** @brief Move assignment */
    Framebuffer &operator=(Framebuffer &&other) noexcept = default;

private:
    /** @brief Create a pipeline layout from model */
    void createFramebuffer(const FramebufferModel &model);
};