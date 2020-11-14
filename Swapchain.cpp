/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Swapchain
 */

#include <iostream>

#include <Kube/Core/StringLiteral.hpp>

#include "Renderer.hpp"

using namespace kF;
using namespace kF::Literal;

Graphics::Swapchain::Swapchain(void)
{
    createSwapchain();
    createImageViews(retreiveImages());
#if KUBE_DEBUG_BUILD
    std::cout << "PresentMode: " << PresentModeName(presentMode()) << std::endl;
    std::cout << "Extent2D: " << extent().width << ", " << extent().height << std::endl;
    std::cout << "Images: " << _imagePairs.size() << std::endl;
#endif
}

void Graphics::Swapchain::createSwapchain(void)
{
    const auto surfaceFormat = parent().surface().getSurfaceFormat();
    const auto presentMode = parent().surface().getPresentMode();
    const auto capabilites = parent().surface().getSurfaceCapabilities();
    const auto extent = parent().surface().getExtent(capabilites);
    const auto imageCount = std::min(capabilites.minImageCount + 1, capabilites.maxImageCount ? capabilites.maxImageCount : capabilites.minImageCount);
    VkSwapchainCreateInfoKHR swapchainInfo {
        sType: VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        pNext: nullptr,
        flags: VkSwapchainCreateFlagsKHR(),
        surface: parent().surface(),
        minImageCount: imageCount,
        imageFormat: surfaceFormat.format,
        imageColorSpace: surfaceFormat.colorSpace,
        imageExtent: extent,
        imageArrayLayers: 1,
        imageUsage: VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
        imageSharingMode: VK_SHARING_MODE_EXCLUSIVE,
        queueFamilyIndexCount: 0,
        pQueueFamilyIndices: nullptr,
        preTransform: capabilites.currentTransform,
        compositeAlpha: VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
        presentMode: static_cast<VkPresentModeKHR>(presentMode),
        clipped: true,
        oldSwapchain: VkSwapchainKHR()
    };

    if (auto res = ::vkCreateSwapchainKHR(parent().logicalDevice(), &swapchainInfo, nullptr, &handle()); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::Swapchain::createSwapchain: Couldn't create swapchain '"s + ErrorMessage(res) + '\'');
    _extent = extent;
    _surfaceFormat = surfaceFormat;
    _presentMode = presentMode;
}

void Graphics::Swapchain::destroySwapchain(void) noexcept
{
    _imagePairs.clear();
    ::vkDestroySwapchainKHR(parent().logicalDevice(), handle(), nullptr);
}

Core::Vector<Graphics::ImageHandle> Graphics::Swapchain::retreiveImages(void)
{
    Core::Vector<ImageHandle> images;

    if (auto res = FillVkContainer(images, &::vkGetSwapchainImagesKHR, parent().logicalDevice(), handle()); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::Swapchain::createImageViews: Couldn't retreive swapchain images '"s + ErrorMessage(res) + '\'');
    return images;
}

void Graphics::Swapchain::createImageViews(Core::Vector<ImageHandle> &&images)
{
    const auto count = images.size();
    ImageViewModel imageViewModel(
        ImageViewCreateFlags::None,
        ImageHandle(),
        ImageViewType::Image2D,
        static_cast<Format>(surfaceFormat().format),
        ComponentMapping {
            r: VK_COMPONENT_SWIZZLE_IDENTITY,
            g: VK_COMPONENT_SWIZZLE_IDENTITY,
            b: VK_COMPONENT_SWIZZLE_IDENTITY,
            a: VK_COMPONENT_SWIZZLE_IDENTITY
        },
        ImageSubresourceRange {
            aspectMask: VK_IMAGE_ASPECT_COLOR_BIT,
            baseMipLevel: 0u,
            levelCount: 1u,
            baseArrayLayer: 0u,
            layerCount: 1u
        }
    );

    _imagePairs.reserve(count);
    for (auto i = 0ul; i < count; ++i) {
        const auto image = images[i];
        imageViewModel.image = image;
        _imagePairs.push(image, imageViewModel);
    }
}
