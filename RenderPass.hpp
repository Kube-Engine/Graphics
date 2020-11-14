/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: RenderPass
 */

#pragma once

#include "VulkanHandle.hpp"

namespace kF::Graphics
{
    class RenderPass;
}

/** @brief Abstraction of a render pass */
class kF::Graphics::RenderPass final : public CachedVulkanHandle<RenderPassHandle>
{
public:
    /** @brief Construct a render pass */
    RenderPass(void) { createRenderPass(); }

    /** @brief Move constructor */
    RenderPass(RenderPass &&other) noexcept = default;

    /** @brief Destruct the render pass */
    ~RenderPass(void) noexcept { destroyRenderPass(); }

    /** @brief Move assignment */
    RenderPass &operator=(RenderPass &&other) noexcept = default;


    /** @brief Callback on render view size changed */
    void onViewSizeChanged(void);

private:
    /** @brief Create a render pass */
    void createRenderPass(void);

    /** @brief Destroy render pass */
    void destroyRenderPass(void) noexcept;
};

#include "RenderPass.ipp"