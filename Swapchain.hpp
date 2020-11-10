/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Swapchain
 */

#pragma once

#include "Image.hpp"

namespace kF::Graphics
{
    class Swapchain;
}

/** @brief Abstraction of renderer swapchain */
class akignas_cacheline kF::Graphics::Swapchain final : public VulkanHandler<VkSwapchainKHR>
{
public:
    /** @brief Construct the swapchain */
    Swapchain(Renderer &renderer);

    /** @brief Move constructor */
    Swapchain(Swapchain &&other) noexcept = default;

    /** @brief Destrut the swapchain */
    ~Swapchain(void) noexcept;

    /** @brief Move assignment */
    Swapchain &operator=(Swapchain &&other) noexcept { swap(other); return *this; }

    /** @brief Get the surface format */
    [[nodiscard]] SurfaceFormat &surfaceFormat(void) noexcept { return _surfaceFormat; }
    [[nodiscard]] const SurfaceFormat &surfaceFormat(void) const noexcept { return _surfaceFormat; }

    /** @brief Get the surface presentationmode */
    [[nodiscard]] PresentMode &presentMode(void) noexcept { return _presentMode; }
    [[nodiscard]] const PresentMode &presentMode(void) const noexcept { return _presentMode; }

    /** @brief Get the extent */
    [[nodiscard]] Extent &extent(void) noexcept { return _extent; }
    [[nodiscard]] const Extent &extent(void) const noexcept { return _extent; }

    /** @brief Get the images buffer of theswapchain */
    [[nodiscard]] auto &images(void) noexcept { return _images; }
    [[nodiscard]] const auto &images(void) const noexcept { return _images; }

    /** @brief Get the image views buffer */
    [[nodiscard]] auto &imageViews(void) noexcept { return _imageViews; }
    [[nodiscard]] const auto &imageViews(void) const noexcept { return _imageViews; }

    /** @brief Swap two swapchains */
    void swap(Swapchain &other) noexcept;

private:
    SurfaceFormat _surfaceFormat;
    PresentMode _presentMode;
    Extent _extent;
    Core::TinyVector<ImageHandle> _images;
    Core::TinyVector<ImageView> _imageViews;

    /** @brief Create the swapchain */
    void createSwapchain(void);

    /** @brief Create swapchain images */
    void retreiveImages(void);

    /** @brief Create swapchain image views */
    void createImageViews(void);
};

static_assert_fit_cacheline(kF::Graphics::Swapchain);

#include "Swapchain.ipp"