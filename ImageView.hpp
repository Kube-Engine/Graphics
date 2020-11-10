/**
 * @ Author: Pierre Veysseyre
 * @ Description: ImageView.hpp
 */

#pragma once

#include "ImageViewModel.hpp"

namespace kF::Graphics
{
    class ImageView;

    using ImageViewHandle = VkImageView;
};

class kF::Graphics::ImageView final : public VulkanHandler<ImageViewHandle>
{
public:
    /** @brief Construct a new ImageView using ImageView model */
    ImageView(Renderer &renderer, const ImageViewModel model);

    /** @brief Move constructor */
    ImageView(ImageView &&other) noexcept = default;

    /** @brief Destruct the buffer */
    ~ImageView(void) noexcept;

    /** @brief Move assignment */
    ImageView &operator=(ImageView &&other) noexcept { swap(other); return *this; }

    /** @brief Swap two instances */
    void swap(ImageView &other) noexcept;

};