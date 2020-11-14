/**
 * @ Author: Pierre Veysseyre
 * @ Description: ImageView.hpp
 */

#pragma once

#include "VulkanHandle.hpp"
#include "ImageViewModel.hpp"

namespace kF::Graphics
{
    class ImageView;
};

/** @brief Abstract an image view */
class kF::Graphics::ImageView final : public VulkanHandle<ImageViewHandle>
{
public:
    /** @brief Construct a new ImageView using ImageView model */
    ImageView(const ImageViewModel &model) { createImageView(model); }

    /** @brief Move constructor */
    ImageView(ImageView &&other) noexcept = default;

    /** @brief Destruct the buffer */
    ~ImageView(void) noexcept;

    /** @brief Move assignment */
    ImageView &operator=(ImageView &&other) noexcept = default;

private:
    /** @brief Create an image view */
    void createImageView(const ImageViewModel &model);
};