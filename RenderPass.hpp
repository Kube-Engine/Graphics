/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Render Pass
 */

#pragma once

#include "VulkanHandler.hpp"

namespace kF
{
    class RenderPass;
}

class kF::RenderPass final : public VulkanHandler<VkRenderPass>
{
public:
    RenderPass(Renderer &renderer);
    RenderPass(RenderPass &&other) = default;
    ~RenderPass(void);

    RenderPass &operator=(RenderPass &&other) = default;

private:
    void createRenderPass(void);
};