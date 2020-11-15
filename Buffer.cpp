/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Buffer
 */

#include <Kube/Core/StringLiteral.hpp>

#include "Renderer.hpp"
#include "Buffer.hpp"

using namespace kF;
using namespace kF::Literal;

Graphics::Buffer::~Buffer(void) noexcept
{
    ::vkDestroyBuffer(parent().logicalDevice(), handle(), nullptr);
}

void Graphics::Buffer::createBuffer(const BufferModel &model)
{
    if (const auto res = ::vkCreateBuffer(parent().logicalDevice(), &model, nullptr, &handle()); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::Buffer::createBuffer: Couldn't create buffer '"s + ErrorMessage(res) + '\'');
}