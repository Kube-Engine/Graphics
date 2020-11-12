/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Renderer sources
 */

#include <stdexcept>

#include <Kube/Core/StringLiteral.hpp>

#include "Renderer.hpp"

using namespace kF;
using namespace kF::Literal;

Graphics::Renderer::Renderer(BackendWindow * const window, const Version applicationVersion) :
    _window(window),
    _instance(*this, applicationVersion),
    _surface(*this),
    _physicalDevice(*this),
    _queueManager(*this),
    _logicalDevice(*this),
    _swapchain(*this),
    _renderPass(*this),
    _pipelineManager(*this),
    _framebufferManager(*this),
    _commandPoolManager(*this)
{
}

void Graphics::Renderer::onViewSizeChanged(void)
{
    // _drawer.waitAllDrawCompleted();
    _swapchain = Swapchain(*this);
    _renderPass = RenderPass(*this);
    _pipelineManager.onViewSizeChanged();
    _framebufferManager.onViewSizeChanged();
    // _commandPoolManager.onViewSizeChanged();
}
