/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: FrameBuffer
 */

#include <iostream>

#include <Kube/Core/StringLiteral.hpp>

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
    auto &extent = parent().swapchain().extent();
    ImageViewHandle imageViewHandle { NullHandle };
    FrameBufferModel model(
        FramebufferCreateFlags::None,
        parent().renderPass(),
        &imageViewHandle, &imageViewHandle + 1,
        extent.width, extent.height, 1u
    );

    _cachedFrames.reserve(count);
    for (auto i = 0ul; i < count; ++i) {
        imageViewHandle = parent().swapchain().imageViews()[i];
        _cachedFrames.caches().push(parent(), model);
    }
}