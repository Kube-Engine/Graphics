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
    VkFramebufferCreateInfo frameBufferInfo {
        sType: VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
        pNext: nullptr,
        flags: VkFramebufferCreateFlags(),
        renderPass: parent().renderPass(),
        attachmentCount: model.imageViews.size(),
        pAttachments: model.imageViews.data(),
        width: parent().swapchain().extent().width,
        height: parent().swapchain().extent().height,
        layers: model.layerCount
    };

    if (auto res = ::vkCreateFramebuffer(parent().logicalDevice(), &frameBufferInfo, nullptr, &handle); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::FrameBufferManager::createFrameBuffers: Couldn't create frameBuffer " + std::to_string(i) + " '" + ErrorMessage(res) + '\'');
}