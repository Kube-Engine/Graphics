/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Swapchain
 */

#pragma once

#include "Image.hpp"
#include "ImageView.hpp"

namespace kF::Graphics
{
    class Swapchain;
}

/** @brief Abstraction of renderer swapchain */
class alignas_cacheline kF::Graphics::Swapchain final : public VulkanHandle<SwapchainHandle>
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
    [[nodiscard]] Extent2D &extent(void) noexcept { return _extent; }
    [[nodiscard]] const Extent2D &extent(void) const noexcept { return _extent; }

    /** @brief Get the number of cached image */
    [[nodiscard]] std::size_t imageCount(void) const noexcept { return _imagePairs.size(); }

    /** @brief Get an image of the swapchain */
    [[nodiscard]] ImageHandle imageAt(const FrameIndex frameIndex) const noexcept { return _imagePairs.at(frameIndex).first; }

    /** @brief Get an image of the swapchain */
    [[nodiscard]] ImageViewHandle imageViewAt(const FrameIndex frameIndex) const noexcept { return _imagePairs.at(frameIndex).second; }

    /** @brief Swap two swapchains */
    void swap(Swapchain &other) noexcept;

private:
    Core::Vector<std::pair<ImageHandle, ImageView>> _imagePairs {};
    Extent2D _extent {};
    SurfaceFormat _surfaceFormat {};
    PresentMode _presentMode { PresentMode::ImmediateKhr };

    /** @brief Create the swapchain */
    void createSwapchain(void);

    /** @brief Create swapchain images */
    [[nodiscard]] Core::Vector<ImageHandle> retreiveImages(void);

    /** @brief Create swapchain image views */
    void createImageViews(Core::Vector<ImageHandle> &&images);
};

static_assert_fit_cacheline(kF::Graphics::Swapchain);

#include "Swapchain.ipp"