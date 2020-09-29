/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Framebuffer
 */

#include <iostream>

#include <Kube/Core/Core.hpp>

#include "Renderer.hpp"

using namespace kF;
using namespace kF::Literal;

FramebufferHandler::FramebufferHandler(Renderer &renderer)
    : RendererObject(renderer)
{
    createFramebuffers();
#ifndef KUBE_NO_DEBUG
    std::cout << "Framebuffers: " << _framebuffers.size() << std::endl;
#endif
}

FramebufferHandler::~FramebufferHandler(void)
{
    for (const auto &framebuffer : _framebuffers)
        ::vkDestroyFramebuffer(parent().getLogicalDevice(), framebuffer, nullptr);
}

void FramebufferHandler::createFramebuffers(void)
{
    VkFramebufferCreateInfo framebufferInfo {
        .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
        .pNext = nullptr,
        .flags = VkFramebufferCreateFlags(),
        .renderPass = parent().getRenderPass(),
        .attachmentCount = 1,
        .pAttachments = nullptr,
        .width = parent().getSwapchain().getExtent().width,
        .height = parent().getSwapchain().getExtent().height,
        .layers = 1
    };
    auto max = parent().getSwapchain().getImageViews().size();

    _framebuffers.reserve(max);
    for (auto i = 0u; i < max; ++i) {
        auto &handle = _framebuffers.emplace_back();
        framebufferInfo.pAttachments = &parent().getSwapchain().getImageViews()[i];
        if (auto res = ::vkCreateFramebuffer(parent().getLogicalDevice(), &framebufferInfo, nullptr, &handle); res != VK_SUCCESS)
            throw std::runtime_error("Framebuffer::createFramebuffers: Couldn't create framebuffer " + std::to_string(i) + " '" + ErrorMessage(res) + '\'');
    }
}