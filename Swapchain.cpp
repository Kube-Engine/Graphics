/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Swapchain
 */

#include <iostream>

#include <Kube/Core/Core.hpp>

#include "Renderer.hpp"

using namespace kF;
using namespace kF::Literal;

Graphics::Swapchain::Swapchain(Renderer &renderer)
    : VulkanHandler<VkSwapchainKHR>(renderer)
{
    createSwapchain();
    retreiveImages();
    createImageViews();
#if KUBE_DEBUG_BUILD
    std::cout << "PresentMode: " << Surface::PresentModeName(presentMode()) << std::endl;
    std::cout << "Extent: " << extent().width << ", " << extent().height << std::endl;
    std::cout << "Images: " << images().size() << std::endl;
    std::cout << "ImageViews: " << imageViews().size() << std::endl;
#endif
}

Graphics::Swapchain::~Swapchain(void) noexcept
{
    for (const auto &imageView : imageViews())
        ::vkDestroyImageView(parent().logicalDevice(), imageView, nullptr);
    ::vkDestroySwapchainKHR(parent().logicalDevice(), handle(), nullptr);
}

void Graphics::Swapchain::createSwapchain(void)
{
    auto surfaceFormat = parent().surface().surfaceFormat();
    auto presentMode = parent().surface().presentMode();
    auto capabilites = parent().surface().surfaceCapabilities();
    auto extent = parent().surface().extent(capabilites);
    auto imageCount = std::min(capabilites.minImageCount + 1, capabilites.maxImageCount ? capabilites.maxImageCount : capabilites.minImageCount);
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
        presentMode: presentMode,
        clipped: true,
        oldSwapchain: VkSwapchainKHR()
    };

    if (auto res = ::vkCreateSwapchainKHR(parent().logicalDevice(), &swapchainInfo, nullptr, &handle()); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::Swapchain::createSwapchain: Couldn't create swapchain '"_str + ErrorMessage(res) + '\'');
    _surfaceFormat = surfaceFormat;
    _presentMode = presentMode;
    _extent = extent;
}

void Graphics::Swapchain::retreiveImages(void)
{
    if (auto res = FillVkContainer(images(), &::vkGetSwapchainImagesKHR, parent().logicalDevice(), handle()); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::Swapchain::createImageViews: Couldn't retreive swapchain images '"_str + ErrorMessage(res) + '\'');
}

void Graphics::Swapchain::createImageViews(void)
{
    const auto max = images().size();
    VkImageViewCreateInfo imageViewInfo {
        sType: VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        pNext: nullptr,
        flags: VkImageViewCreateFlags(),
        image: VkImage(),
        viewType: VK_IMAGE_VIEW_TYPE_2D,
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