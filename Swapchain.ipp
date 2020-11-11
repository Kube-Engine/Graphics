/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Swapchain
 */

inline void kF::Graphics::Swapchain::swap(Swapchain &other) noexcept
{
    VulkanHandle<VkSwapchainKHR>::swap(other);
    std::swap(_surfaceFormat, other._surfaceFormat);
    std::swap(_presentMode, other._presentMode);
    std::swap(_extent, other._extent);
    _images.swap(other._images);
    _imageViews.swap(other._imageViews);
}