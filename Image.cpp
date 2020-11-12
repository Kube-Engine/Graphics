/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Image
 */

#include <Kube/Core/StringLiteral.hpp>

#include "Renderer.hpp"
#include "Image.hpp"

using namespace kF;
using namespace kF::Literal;

Graphics::Image::~Image(void) noexcept
{
    ::vkDestroyImage(parent().logicalDevice(), handle(), nullptr);
}

void Graphics::Image::createImage(const ImageModel &model)
{
    if (auto res = ::vkCreateImage(parent().logicalDevice(), &model, nullptr, &handle()); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::Image::createImage: Couldn't create image '"s + ErrorMessage(res) + '\'');
}