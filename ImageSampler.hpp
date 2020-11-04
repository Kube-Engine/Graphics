/**
 * @ Author: Pierre Veysseyre
 * @ Description: ImageSampler.hpp
 */

#pragma once

#include "VulkanHandler.hpp"
#include "ImageSamplerModel.hpp"

namespace kF::Graphics
{
    class ImageSample;

    using DeviceImageSampler = VkSampler;
};

class kF::Graphics::ImageSample final : public VulkanHandler<DeviceImageSampler>
{
public:
    /** @brief Construct a new ImageSampler using ImageSampler model */
    ImageSampler(Renderer &renderer, const ImageSamplerModel model);

    /** @brief Move constructor */
    ImageSampler(ImageSampler &&other) noexcept : VulkanHandler<DeviceImageSampler>(other.parent()) { swap(other); }

    /** @brief Destruct the buffer */
    ~ImageSampler(void) noexcept;

    /** @brief Move assignment */
    ImageSampler &operator=(ImageSampler &&other) noexcept { swap(other); return *this; }

    /** @brief Swap two instances */
    void swap(ImageSampler &other) noexcept;
private:
};