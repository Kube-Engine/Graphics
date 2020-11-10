/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Renderer sources
 */

#include <stdexcept>

#include "Renderer.hpp"

using namespace kF;
using namespace kF::Literal;

Graphics::Renderer::Renderer(BackendWindow *window, const Version applicationVersion) :
    _window(window),
    _instance(*this, applicationVersion),
    _surface(*this),
    _physicalDevice(*this),
    _queueHandler(*this),
    _logicalDevice(*this),
    _swapchain(*this),
    _renderPass(*this),
    _pipelinePool(*this),
    _frameBufferManager(*this),
    _commandPool(*this),
    _bufferPool(*this),
    _drawer(*this)
{
}

void Graphics::Renderer::draw(void)
{
}

void Graphics::Renderer::onViewSizeChanged(void)
{
    _drawer.waitAllDrawCompleted();
    _swapchain = Swapchain(*this);
    _renderPass = RenderPass(*this);
    _pipelinePool.onViewSizeChanged();
    _frameBufferManager = FrameBufferManager(*this);
    _commandPool.onViewSizeChanged();
}
