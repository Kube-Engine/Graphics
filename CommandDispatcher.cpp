/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Command dispatcher
 */

#include "CommandDispatcher.hpp"
#include "Renderer.hpp"

using namespace kF;

Graphics::CommandDispatcher::CommandDispatcher(Renderer &renderer) : RendererObject(renderer)
{

}

Graphics::CommandPoolInstance::~CommandPoolInstance(void)
{
    if (_pool)
        _parent->releaseInstance(_pool);
}

Graphics::CommandPoolInstance Graphics::CommandDispatcher::reserveCommandPool(const QueueType type)
{

}

void Graphics::CommandDispatcher::releaseInstance(CommandPool *pool)
{

}

void Graphics::CommandDispatcher::onViewSizeChanged(void)
{
    for (auto &pool : _pools)
        pool->onViewSizeChanged();
}