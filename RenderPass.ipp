/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: RenderPass
 */

inline void kF::Graphics::RenderPass::onViewSizeChanged(void)
{
    destroyRenderPass();
    createRenderPass();
}