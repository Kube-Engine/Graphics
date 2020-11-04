/**
 * @ Author: Pierre Veysseyre
 * @ Description: ImageModel.hpp
 */

#pragma once

#include "Vulkan.hpp"

namespace kF::Graphics
{
    struct ImageModel;
};

struct kF::Graphics::ImageModel
{
    enum class Type {
        Image1D = VK_IMAGE_TYPE_1D,
        Image2D = VK_IMAGE_TYPE_2D,
        Image3D = VK_IMAGE_TYPE_3D
    };

    struct Dimensions {
        uint32_t width;
        uint32_t height;
        uint32_t depth;
    };

    Type type;
    Dimensions dimension;
    uint32_t mipMapCount;
    uint32_t arrayLayerCount;
    VkFormat format;
    VkImageTilling tilling;
    VkImageLayout initialLayout;
    VkImageUsageFlags usage;
    VkSharingMode sharingMode;
    VkSampleCountFlagBits samplingDetail;
};