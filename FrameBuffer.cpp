/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: FrameBuffer
 */

#include "Renderer.hpp"

using namespace kF;

Graphics::FrameBuffer::~FrameBuffer(void)
{
    ::vkDestroyFrameBuffer(parent().logicalDevice(), handle(), nullptr);
}

void Graphics::FrameBuffer::createFrameBuffer(const FrameBufferModel &model)
{
    if (auto res = ::vkCreateFramebuffer(parent().logicalDevice(), &model, nullptr, &handle); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::FrameBufferManager::createFrameBuffers: Couldn't create frameBuffer " + std::to_string(i) + " '" + ErrorMessage(res) + '\'');
}