/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Framebuffer
 */

#include <iostream>

#include "Renderer.hpp"
#include "FramebufferManager.hpp"

using namespace kF;

Graphics::FramebufferManager::FramebufferManager(void)
{
    createFramebuffers();
#if KUBE_DEBUG_BUILD
    std::cout << "Frame buffers: " << framebuffers().size() << std::endl;
#endif
}

void Graphics::FramebufferManager::createFramebuffers(void)
{
    const auto count = parent().cachedFrameCount();
    auto &extent = parent().swapchain().extent();
    ImageViewHandle imageViewHandle { NullHandle };
    const FramebufferModel model(
        FramebufferCreateFlags::None,
        parent().renderPass(),
        &imageViewHandle, &imageViewHandle + 1,
        extent.width, extent.height, 1u
    );

    _cachedFrames.caches().reserve(count);
    for (auto i = 0ul; i < count; ++i) {
        imageViewHandle = parent().swapchain().imageViewAt(i);
        _cachedFrames.caches().push(model);
    }
}