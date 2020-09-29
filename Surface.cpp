/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Surface
 */

#include <stdexcept>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

#include <Kube/Core/Core.hpp>

#include "Renderer.hpp"

using namespace kF;
using namespace kF::Literal;

Surface::Surface(Renderer &renderer)
    : VulkanHandler<VkSurfaceKHR>(renderer)
{
    if (!::SDL_Vulkan_CreateSurface(parent().getBackendWindow(), parent().getInstance(), &handle()))
        throw std::runtime_error("Surface::Surface: Couldn't create surface '"_str + ::SDL_GetError() + '\'');
}

Surface::~Surface(void)
{
    ::vkDestroySurfaceKHR(parent().getInstance(), handle(), nullptr);
}

SurfaceFormat Surface::getSurfaceFormat(void) const
{
    std::vector<SurfaceFormat> formats;

    if (auto res = FillVkContainer(formats, &::vkGetPhysicalDeviceSurfaceFormatsKHR, parent().getPhysicalDevice(), handle()); res != VK_SUCCESS || formats.empty())
        throw std::runtime_error("Surface::getSurfaceFormat: Couldn't retreive physical device surface format '"_str + ErrorMessage(res) + '\'');
    for (const auto &format : formats) {
        if (format.format != VK_FORMAT_B8G8R8A8_UNORM || format.colorSpace != VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
            continue;
        return format;
    }
    std::cout << "Surface::getSurfaceFormat: Couldn't find SurfaceFormat with B8G8R8A8_UNORM and SRGB_NONLINEAR, using first avaible format" << std::endl;
    return formats[0];
}

PresentMode Surface::getPresentMode(void) const
{
    std::vector<PresentMode> modes;

    if (auto res = FillVkContainer(modes, &::vkGetPhysicalDeviceSurfacePresentModesKHR, parent().getPhysicalDevice(), handle()); res != VK_SUCCESS)
        throw std::runtime_error("Surface::getPresentMode: Couldn't retreive physical device present modes");
    for (const auto &mode : modes) {
        if (mode == VK_PRESENT_MODE_MAILBOX_KHR)
            return mode;
    }
    return VK_PRESENT_MODE_FIFO_KHR;
}

SurfaceCapabilities Surface::getSurfaceCapabilities(void) const
{
    SurfaceCapabilities capabilities {};

    if (auto res = ::vkGetPhysicalDeviceSurfaceCapabilitiesKHR(parent().getPhysicalDevice(), handle(), &capabilities); res != VK_SUCCESS)
        throw std::runtime_error("Surface::getSurfaceCapabilities: Couldn't retreive physical device surface capabilities '"_str + ErrorMessage(res) + '\'');
    return capabilities;
}

Extent Surface::getExtent(const SurfaceCapabilities &capabilities) const
{
    int width = 0, height = 0;

    if (capabilities.currentExtent.width != UINT32_MAX && capabilities.currentExtent.height != UINT32_MAX)
        return capabilities.currentExtent;
    ::SDL_GetWindowSize(parent().getBackendWindow(), &width, &height);
    return {
        std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, static_cast<std::uint32_t>(width))),
        std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, static_cast<std::uint32_t>(height)))
    };
}

const char *Surface::PresentModeName(const PresentMode type) noexcept
{
    switch (type) {
    case VK_PRESENT_MODE_IMMEDIATE_KHR:
        return "PRESENT_MODE_IMMEDIATE_KHR";
    case VK_PRESENT_MODE_MAILBOX_KHR:
        return "PRESENT_MODE_MAILBOX_KHR";
    case VK_PRESENT_MODE_FIFO_KHR:
        return "PRESENT_MODE_FIFO_KHR";
    case VK_PRESENT_MODE_FIFO_RELAXED_KHR:
        return "PRESENT_MODE_FIFO_RELAXED_KHR";
    case VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR:
        return "PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR";
    case VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR:
        return "PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR";
    // case VK_PRESENT_MODE_RANGE_SIZE_KHR:
    //     return "PRESENT_MODE_RANGE_SIZE_KHR";
    default:
        return "UNKNOWN_PRESENT_MODE";
    }
}