/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Surface
 */

#pragma once

#include "BackendWindow.hpp"
#include "VulkanHandle.hpp"

namespace kF::Graphics
{
    class Surface;

    /** @brief Vulkan surface format */
    using SurfaceFormat = VkSurfaceFormatKHR;

    /** @brief Vulkan presentation mode*/
    using PresentMode = VkPresentModeKHR;

    /** @brief Vulkan presentation mode*/
    using SurfaceCapabilities = VkSurfaceCapabilitiesKHR;

    /** @brief Vulkan extent */
    using Extent = VkExtent2D;
}

/** @brief Abstraction of a render surface */
class kF::Graphics::Surface final : public VulkanHandle<VkSurfaceKHR>
{
public:
    /** @brief Construct a surface */
    Surface(Renderer &renderer);

    /** @brief Move constructor */
    Surface(Surface &&other) noexcept = default;

    /** @brief Destruct the surface */
    ~Surface(void) noexcept;

    /** @brief Move assignment */
    Surface &operator=(Surface &&other) noexcept = default;

    /** @brief Get the surface format */
    [[nodiscard]] SurfaceFormat surfaceFormat(void) const;

    /** @brief Get the presentation mode */
    [[nodiscard]] PresentMode presentMode(void) const;

    /** @brief Get the surface capabilities */
    [[nodiscard]] SurfaceCapabilities surfaceCapabilities(void) const;

    /** @brief Get the extent */
    [[nodiscard]] Extent extent(const SurfaceCapabilities &capabilities) const;

    /** @brief Get literal of a 'PresentMode' enumeration */
    [[nodiscard]] static const char *PresentModeName(const PresentMode type) noexcept;

private:
};