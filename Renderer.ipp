/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Renderer
 */

inline void kF::Graphics::Renderer::dispatchFrameAcquired(const FrameIndex frameIndex)
{
    _framebufferManager.onFrameAquired(frameIndex);
    _commandPoolManager.onFrameAquired(frameIndex);
    _frameAcquiredDispatcher.dispatch(frameIndex);
}

inline void kF::Graphics::Renderer::dispatchViewSizeChanged(void)
{
    _logicalDevice.waitIdle();
    _swapchain.onViewSizeChanged();
    _renderPass.onViewSizeChanged();
    _pipelineManager.onViewSizeChanged();
    _framebufferManager.onViewSizeChanged();
    _viewSizeDispatcher.dispatch();
}
