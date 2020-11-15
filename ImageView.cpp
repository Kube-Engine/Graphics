/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: ImageView
 */

#include <Kube/Core/StringLiteral.hpp>

#include "Renderer.hpp"
#include "ImageView.hpp"

using namespace kF;
using namespace kF::Literal;

Graphics::ImageView::~ImageView(void) noexcept
{
    ::vkDestroyImageView(parent().logicalDevice(), handle(), nullptr);
}

void Graphics::ImageView::createImageView(const ImageViewModel &model)
{
    if (const auto res = ::vkCreateImageView(parent().logicalDevice(), &model, nullptr, &handle()); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::ImageView::createImageView: Couldn't create image view '"s + ErrorMessage(res) + '\'');
}