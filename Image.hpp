/**
 * @ Author: Pierre Veysseyre
 * @ Description: Image.hpp
 */

#pragma once

#include "VulkanHandler.hpp"
#include "ImageModel.hpp"

namespace kF::Graphics
{
    class Image;

    using DeviceImage = VkImage;
};

class kF::Graphics::Image final : public VulkanHandler<DeviceImage>
{
public:
    /** @brief Construct a new Image using image model */
    Image(Renderer &renderer, const ImageModel model);

    /** @brief Move constructor */
    Image(Image &&other) noexcept : VulkanHandler<DeviceImage>(other.parent()) { swap(other); }

    /** @brief Destruct the buffer */
    ~Image(void) noexcept;

    /** @brief Move assignment */
    Image &operator=(Image &&other) noexcept { swap(other); return *this; }

    /** @brief Swap two instances */
    void swap(Image &other) noexcept;

private:

};