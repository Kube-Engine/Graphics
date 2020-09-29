/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Surface
 */

#pragma once

#include "BackendWindow.hpp"
#include "VulkanHandler.hpp"

namespace kF
{
    class Surface;

    using SurfaceFormat = VkSurfaceFormatKHR;
    using PresentMode = VkPresentModeKHR;
    using SurfaceCapabilities = VkSurfaceCapabilitiesKHR;
    using Extent = VkExtent2D;
}

class kF::Surface final : public VulkanHandler<VkSurfaceKHR>
{
public:
    Surface(Renderer &renderer);
    Surface(Surface &&other) = default;
    ~Surface(void);

    Surface &operator=(Surface &&other) = default;

    [[nodiscard]] SurfaceFormat getSurfaceFormat(void) const;
    [[nodiscard]] PresentMode getPresentMode(void) const;
    [[nodiscard]] SurfaceCapabilities getSurfaceCapabilities(void) const;
    [[nodiscard]] Extent getExtent(const SurfaceCapabilities &capabilities) const;

    [[nodiscard]] static const char *PresentModeName(const PresentMode type) noexcept;

private:
};