/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Surface
 */

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

#include <Kube/Core/StringLiteral.hpp>

#include "Renderer.hpp"
#include "Surface.hpp"

using namespace kF;
using namespace kF::Literal;

const char *Graphics::PresentModeName(const PresentMode type) noexcept
{
    switch (type) {
    case PresentMode::ImmediateKhr:
        return "ImmediateKhr";
    case PresentMode::MailboxKhr:
        return "MailboxKhr";
    case PresentMode::FifoKhr:
        return "FifoKhr";
    case PresentMode::FifoRelaxedKhr:
        return "FifoRelaxedKhr";
    case PresentMode::SharedDemandRefreshKhr:
        return "SharedDemandRefreshKhr";
    case PresentMode::SharedContinuousRefreshKhr:
        return "SharedContinuousRefreshKhr";
    default:
        return "UnknownPresentMode";
    }
}

Graphics::Surface::~Surface(void) noexcept
{
    ::vkDestroySurfaceKHR(parent().instance(), handle(), nullptr);
}

Graphics::SurfaceFormat Graphics::Surface::getSurfaceFormat(void) const
{
    std::vector<SurfaceFormat> formats;

    if (auto res = FillVkContainer(formats, &::vkGetPhysicalDeviceSurfaceFormatsKHR, parent().physicalDevice(), handle()); res != VK_SUCCESS || formats.empty())
        throw std::runtime_error("Graphics::Surface::surfaceFormat: Couldn't retreive physical device surface format '"s + ErrorMessage(res) + '\'');
    for (const auto &format : formats) {
        if (format.format != VK_FORMAT_B8G8R8A8_UNORM || format.colorSpace != VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
            continue;
        return format;
    }
    std::cout << "Graphics::Surface::surfaceFormat: Couldn't find SurfaceFormat with B8G8R8A8_UNORM and SRGB_NONLINEAR, using first avaible format" << std::endl;
    return formats[0];
}

Graphics::PresentMode Graphics::Surface::getPresentMode(void) const
{
    std::vector<VkPresentModeKHR> modes;

    if (auto res = FillVkContainer(modes, &::vkGetPhysicalDeviceSurfacePresentModesKHR, parent().physicalDevice(), handle()); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::Surface::getPresentMode: Couldn't retreive physical device present modes");
    for (const auto &mode : modes) {
        if (static_cast<PresentMode>(mode) == PresentMode::MailboxKhr)
            return static_cast<PresentMode>(mode);
    }
    return PresentMode::FifoKhr;
}

Graphics::SurfaceCapabilities Graphics::Surface::getSurfaceCapabilities(void) const
{
    SurfaceCapabilities capabilities {};

    if (auto res = ::vkGetPhysicalDeviceSurfaceCapabilitiesKHR(parent().physicalDevice(), handle(), &capabilities); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::Surface::surfaceCapabilities: Couldn't retreive physical device surface capabilities '"s + ErrorMessage(res) + '\'');
    return capabilities;
}

Graphics::Extent2D Graphics::Surface::getExtent(const SurfaceCapabilities &capabilities) const
{
    int width = 0, height = 0;

    if (capabilities.currentExtent.width != UINT32_MAX && capabilities.currentExtent.height != UINT32_MAX)
        return capabilities.currentExtent;
    ::SDL_GetWindowSize(parent().backendWindow(), &width, &height);
    return Extent2D {
        width: std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, static_cast<std::uint32_t>(width))),
        height: std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, static_cast<std::uint32_t>(height))),
    };
}

void Graphics::Surface::createSurface(void)
{
    if (!::SDL_Vulkan_CreateSurface(parent().backendWindow(), parent().instance(), &handle()))
        throw std::runtime_error("Graphics::Surface::Surface: Couldn't create surface '"s + ::SDL_GetError() + '\'');
}