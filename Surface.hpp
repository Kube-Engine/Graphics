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

    /** @brief Get literal of a 'PresentMode' enumeration */
    [[nodiscard]] const char *PresentModeName(const PresentMode type) noexcept;
}

/** @brief Abstraction of a render surface */
class kF::Graphics::Surface final : public CachedVulkanHandle<SurfaceHandle>
{
public:
    /** @brief Construct a surface */
    Surface(void) { createSurface(); }

    /** @brief Move constructor */
    Surface(Surface &&other) noexcept = default;

    /** @brief Destruct the surface */
    ~Surface(void) noexcept;

    /** @brief Move assignment */
    Surface &operator=(Surface &&other) noexcept = default;

    /** @brief Get the surface format */
    [[nodiscard]] SurfaceFormat getSurfaceFormat(void) const;

    /** @brief Get the presentation mode */
    [[nodiscard]] PresentMode getPresentMode(void) const;

    /** @brief Get the surface capabilities */
    [[nodiscard]] SurfaceCapabilities getSurfaceCapabilities(void) const;

    /** @brief Get the extent */
    [[nodiscard]] Extent2D getExtent(const SurfaceCapabilities &capabilities) const;

private:
    /** @brief Create a surface */
    void createSurface(void);
};