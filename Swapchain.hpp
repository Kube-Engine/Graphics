/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Swapchain
 */

#pragma once

#include "VulkanHandler.hpp"

namespace kF::Graphics
{
    class Swapchain;

    using Image = VkImage;
    using Images = std::vector<Image>;
    using ImageView = VkImageView;
    using ImageViews = std::vector<ImageView>;
}

/** @brief Abstraction of renderer swapchain */
class kF::Graphics::Swapchain final : public VulkanHandler<VkSwapchainKHR>
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
    [[nodiscard]] SurfaceFormat &getSurfaceFormat(void) noexcept { return _surfaceFormat; }
    [[nodiscard]] const SurfaceFormat &getSurfaceFormat(void) const noexcept { return _surfaceFormat; }

    /** @brief Get the surface presentationmode */
    [[nodiscard]] PresentMode &getPresentMode(void) noexcept { return _presentMode; }
    [[nodiscard]] const PresentMode &getPresentMode(void) const noexcept { return _presentMode; }

    /** @brief Get the extent */
    [[nodiscard]] Extent &getExtent(void) noexcept { return _extent; }
    [[nodiscard]] const Extent &getExtent(void) const noexcept { return _extent; }

    /** @brief Get the images buffer of theswapchain */
    [[nodiscard]] Images &getImages(void) noexcept { return _images; }
    [[nodiscard]] const Images &getImages(void) const noexcept { return _images; }

    /** @brief Get the image views buffer */
    [[nodiscard]] ImageViews &getImageViews(void) noexcept { return _imageViews; }
    [[nodiscard]] const ImageViews &getImageViews(void) const noexcept { return _imageViews; }

    /** @brief Swap two swapchains */
    void swap(Swapchain &other) noexcept;

private:
    SurfaceFormat _surfaceFormat;
    PresentMode _presentMode;
    Extent _extent;
    Images _images;
    ImageViews _imageViews;

    /** @brief Create the swapchain */
    void createSwapchain(void);

    /** @brief Create swapchain images */
    void retreiveImages(void);

    /** @brief Create swapchain image views */
    void createImageViews(void);
};