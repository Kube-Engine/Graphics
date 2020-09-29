/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Swapchain
 */

#include <iostream>

#include <Kube/Core/Core.hpp>

#include "Renderer.hpp"

using namespace kF;
using namespace kF::Literal;

Swapchain::Swapchain(Renderer &renderer)
    : VulkanHandler<VkSwapchainKHR>(renderer)
{
    createSwapchain();
    retreiveImages();
    createImageViews();
#ifndef KUBE_NO_DEBUG
    std::cout << "PresentMode: " << Surface::PresentModeName(getPresentMode()) << std::endl;
    std::cout << "Extent: " << getExtent().width << ", " << getExtent().height << std::endl;
    std::cout << "Images: " << getImages().size() << std::endl;
    std::cout << "ImageViews: " << getImageViews().size() << std::endl;
#endif
}

Swapchain::~Swapchain(void)
{
    for (const auto &imageView : getImageViews())
        ::vkDestroyImageView(parent().getLogicalDevice(), imageView, nullptr);
    ::vkDestroySwapchainKHR(parent().getLogicalDevice(), handle(), nullptr);
}

void Swapchain::createSwapchain(void)
{
    auto surfaceFormat = parent().getSurface().getSurfaceFormat();
    auto presentMode = parent().getSurface().getPresentMode();
    auto capabilites = parent().getSurface().getSurfaceCapabilities();
    auto extent = parent().getSurface().getExtent(capabilites);
    auto imageCount = std::min(capabilites.minImageCount + 1, capabilites.maxImageCount ? capabilites.maxImageCount : capabilites.minImageCount);
    VkSwapchainCreateInfoKHR swapchainInfo {
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .pNext = nullptr,
        .flags = VkSwapchainCreateFlagsKHR(),
        .surface = parent().getSurface(),
        .minImageCount = imageCount,
        .imageFormat = surfaceFormat.format,
        .imageColorSpace = surfaceFormat.colorSpace,
        .imageExtent = extent,
        .imageArrayLayers = 1,
        .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
        .imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
        .queueFamilyIndexCount = 0,
        .pQueueFamilyIndices = nullptr,
        .preTransform = capabilites.currentTransform,
        .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
        .presentMode = presentMode,
        .clipped = true,
        .oldSwapchain = VkSwapchainKHR()
    };

    if (auto res = ::vkCreateSwapchainKHR(parent().getLogicalDevice(), &swapchainInfo, nullptr, &handle()); res != VK_SUCCESS)
        throw std::runtime_error("Swapchain::createSwapchain: Couldn't create swapchain '"_str + ErrorMessage(res) + '\'');
    getSurfaceFormat() = surfaceFormat;
    getPresentMode() = presentMode;
    getExtent() = extent;
}

void Swapchain::retreiveImages(void)
{
    if (auto res = FillVkContainer(getImages(), &::vkGetSwapchainImagesKHR, parent().getLogicalDevice(), handle()); res != VK_SUCCESS)
        throw std::runtime_error("Swapchain::createImageViews: Couldn't retreive swapchain images '"_str + ErrorMessage(res) + '\'');
}

void Swapchain::createImageViews(void)
{
    auto max = getImages().size();
    VkImageViewCreateInfo imageViewInfo {
        .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        .pNext = nullptr,
        .flags = VkImageViewCreateFlags(),
        .image = VkImage(),
        .viewType = VK_IMAGE_VIEW_TYPE_2D,
        .format = getSurfaceFormat().format,
        .components = {
            .r = VK_COMPONENT_SWIZZLE_IDENTITY,
            .g = VK_COMPONENT_SWIZZLE_IDENTITY,
            .b = VK_COMPONENT_SWIZZLE_IDENTITY,
            .a = VK_COMPONENT_SWIZZLE_IDENTITY
        },
        .subresourceRange = {
            .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
            .baseMipLevel = 0,
            .levelCount = 1,
            .baseArrayLayer = 0,
            .layerCount = 1
        }
    };

    getImageViews().resize(max);
    for (auto i = 0u; i < max; ++i) {
        imageViewInfo.image = getImages()[i];
        if (auto res = ::vkCreateImageView(parent().getLogicalDevice(), &imageViewInfo, nullptr, &getImageViews()[i]); res != VK_SUCCESS)
            throw std::runtime_error("Swapchain::createImageViews: Couldn't create image " + std::to_string(i) + " '" + ErrorMessage(res) + '\'');
    }
}

void Swapchain::swap(Swapchain &other)
{
    VulkanHandler<VkSwapchainKHR>::swap(other);
    std::swap(_surfaceFormat, other._surfaceFormat);
    std::swap(_presentMode, other._presentMode);
    std::swap(_extent, other._extent);
    std::swap(_images, other._images);
    std::swap(_imageViews, other._imageViews);
}