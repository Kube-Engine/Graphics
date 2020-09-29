/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Command dispatcher
 */

#include "CommandDispatcher.hpp"
#include "Renderer.hpp"

using namespace kF;

CommandDispatcher::CommandDispatcher(Renderer &renderer)
{

}

CommandDispatcher::~CommandDispatcher(void)
{

}

CommandPoolInstance CommandDispatcher::reserveCommandPool(void)
{

}

void CommandDispatcher::releaseInstance(CommandPool *pool)
{

}

void CommandDispatcher::onViewSizeChanged(void)
{
    for (auto &pool : pools)
        pool->onViewSizeChanged();
}