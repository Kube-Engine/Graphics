/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: FrameBuffer
 */

#include <iostream>

#include <Kube/Core/Core.hpp>

#include "Renderer.hpp"

using namespace kF;
using namespace kF::Literal;

Graphics::FrameBufferManager::FrameBufferManager(Renderer &renderer)
    : RendererObject(renderer), _cachedFrames(0)
{
    createFrameBuffers();
#if KUBE_DEBUG_BUILD
    std::cout << "Frame buffers: " << frameBuffers().size() << std::endl;
#endif
}

void Graphics::FrameBufferManager::createFrameBuffers(void)
{
    const auto count = parent().cachedFrameCount();
    FrameBufferModel model {
        imageViews: { 1u },
        layoutCount: 1u
    };

    _cachedFrames.caches().reserve(count);
    for (auto i = 0ul; i < count; ++i) {
        model.imageViews.front() = parent().swapchain().imageViews()[i];
        _cachedFrames.caches().push(parent(), model);
    }
}