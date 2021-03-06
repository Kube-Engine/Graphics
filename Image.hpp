/**
 * @ Author: Pierre Veysseyre
 * @ Description: Image.hpp
 */

#pragma once

#include "VulkanHandle.hpp"
#include "ImageModel.hpp"

namespace kF::Graphics
{
    class Image;
};

/** @brief Abstract an image */
class kF::Graphics::Image final : public VulkanHandle<ImageHandle>
{
public:
    /** @brief Construct a new Image using image model */
    Image(const ImageModel &model) { createImage(model); }

    /** @brief Move constructor */
    Image(Image &&other) noexcept = default;

    /** @brief Destruct the buffer */
    ~Image(void) noexcept;

    /** @brief Move assignment */
    Image &operator=(Image &&other) noexcept = default;

private:
    /** @brief Create an image */
    void createImage(const ImageModel &model);
};