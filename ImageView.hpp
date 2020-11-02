/**
 * @ Author: Pierre Veysseyre
 * @ Description: ImageView.hpp
 */

#pragma once

#include "VulkanHandler.hpp"
#include "ImageViewModel.hpp"

namespace kF::Graphics
{
    class ImageView;

    using DeviceImageView = VkImageView;
};

class kF::Graphics::ImageView final : public VulkanHandler<DeviceImageView>
{
public:
    /** @brief Construct a new ImageView using ImageView model */
    ImageView(Renderer &renderer, const ImageViewModel model);

    /** @brief Move constructor */
    ImageView(ImageView &&other) noexcept : VulkanHandler<DeviceImageView>(other.parent()) { swap(other); }

    /** @brief Destruct the buffer */
    ~ImageView(void) noexcept;

    /** @brief Move assignment */
    ImageView &operator=(ImageView &&other) noexcept { swap(other); return *this; }

    /** @brief Swap two instances */
    void swap(ImageView &other) noexcept;

};