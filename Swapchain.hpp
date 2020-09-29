/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Swapchain
 */

#pragma once

#include "VulkanHandler.hpp"

namespace kF
{
    class Swapchain;

    using Image = VkImage;
    using Images = std::vector<Image>;
    using ImageView = VkImageView;
    using ImageViews = std::vector<ImageView>;
}

class kF::Swapchain final : public VulkanHandler<VkSwapchainKHR>
{
public:
    Swapchain(Renderer &renderer);
    Swapchain(Swapchain &&other) = default;
    ~Swapchain(void);

    Swapchain &operator=(Swapchain &&other) { swap(other); return *this; }

    [[nodiscard]] SurfaceFormat &getSurfaceFormat(void) noexcept { return _surfaceFormat; }
    [[nodiscard]] const SurfaceFormat &getSurfaceFormat(void) const noexcept { return _surfaceFormat; }

    [[nodiscard]] PresentMode &getPresentMode(void) noexcept { return _presentMode; }
    [[nodiscard]] const PresentMode &getPresentMode(void) const noexcept { return _presentMode; }

    [[nodiscard]] Extent &getExtent(void) noexcept { return _extent; }
    [[nodiscard]] const Extent &getExtent(void) const noexcept { return _extent; }

    [[nodiscard]] Images &getImages(void) noexcept { return _images; }
    [[nodiscard]] const Images &getImages(void) const noexcept { return _images; }

    [[nodiscard]] ImageViews &getImageViews(void) noexcept { return _imageViews; }
    [[nodiscard]] const ImageViews &getImageViews(void) const noexcept { return _imageViews; }

    void swap(Swapchain &other);

private:
    SurfaceFormat _surfaceFormat;
    PresentMode _presentMode;
    Extent _extent;
    Images _images;
    ImageViews _imageViews;

    void createSwapchain(void);
    void retreiveImages(void);
    void createImageViews(void);
};