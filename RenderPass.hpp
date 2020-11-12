/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Render Pass
 */

#pragma once

#include "VulkanHandle.hpp"

namespace kF::Graphics
{
    class RenderPass;
}

/** @brief Abstraction of a render pass */
class kF::Graphics::RenderPass final : public VulkanHandle<RenderPassHandle>
{
public:
    /** @brief Construct a render pass */
    RenderPass(Renderer &renderer) : VulkanHandle<RenderPassHandle>(renderer)
        { createRenderPass(); }

    /** @brief Move constructor */
    RenderPass(RenderPass &&other) noexcept = default;

    /** @brief Destruct the render pass */
    ~RenderPass(void) noexcept;

    /** @brief Move assignment */
    RenderPass &operator=(RenderPass &&other) noexcept = default;

private:
    /** @brief Create a render pass */
    void createRenderPass(void);
};