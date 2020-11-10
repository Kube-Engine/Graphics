/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: ImageView
 */

#include "Renderer.hpp"

using namespace kF;

Graphics::ImageView::~ImageView(void) noexcept
{
    ::vkDestroyImageView(parent().logicalDevice(), handle(), nullptr);
}

void Graphics::ImageView::createImageView(const ImageViewModel &model)
{
    const auto max = images().size();
    VkImageViewCreateInfo imageViewInfo {
        sType: VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        pNext: nullptr,
        flags: VkImageViewCreateFlags(),
        image: model.image,
        viewType: static_cast<VkImageViewType>(model.type),
        format: surfaceFormat().format,
        components: {
            r: VK_COMPONENT_SWIZZLE_IDENTITY,
            g: VK_COMPONENT_SWIZZLE_IDENTITY,
            b: VK_COMPONENT_SWIZZLE_IDENTITY,
            a: VK_COMPONENT_SWIZZLE_IDENTITY
        },
        subresourceRange: {
            aspectMask: VK_IMAGE_ASPECT_COLOR_BIT,
            baseMipLevel: 0,
            levelCount: 1,
            baseArrayLayer: 0,
            layerCount: 1
        }
    };

    imageViews().resize(max);
    for (auto i = 0u; i < max; ++i) {
        imageViewInfo.image = images()[i];
        if (auto res = ::vkCreateImageView(parent().logicalDevice(), &imageViewInfo, nullptr, &imageViews()[i]); res != VK_SUCCESS)
            throw std::runtime_error("Graphics::Swapchain::createImageViews: Couldn't create image " + std::to_string(i) + " '" + ErrorMessage(res) + '\'');
    }
}