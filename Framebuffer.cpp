/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Framebuffer
 */

#include <Kube/Core/StringLiteral.hpp>

#include "Renderer.hpp"
#include "Framebuffer.hpp"

using namespace kF;
using namespace kF::Literal;

Graphics::Framebuffer::~Framebuffer(void)
{
    ::vkDestroyFramebuffer(parent().logicalDevice(), handle(), nullptr);
}

void Graphics::Framebuffer::createFramebuffer(const FramebufferModel &model)
{
    if (auto res = ::vkCreateFramebuffer(parent().logicalDevice(), &model, nullptr, &handle()); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::FramebufferManager::createFramebuffers: Couldn't create framebuffer '"s + ErrorMessage(res) + '\'');
}