/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Swapchain
 */

inline void kF::Graphics::Swapchain::swap(Swapchain &other) noexcept
{
    VulkanHandler<VkSwapchainKHR>::swap(other);
    std::swap(_surfaceFormat, other._surfaceFormat);
    std::swap(_presentMode, other._presentMode);
    std::swap(_extent, other._extent);
    std::swap(_images, other._images);
    std::swap(_imageViews, other._imageViews);
}