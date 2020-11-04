/**
 * @ Author: Pierre Veysseyre
 * @ Description: ImageViewModel.hpp
 */

#pragma once

#include "Vulkan.hpp"
#include "Image.hpp"

namespace kF::Graphics
{
    struct ImageViewModel;
};

struct kF::Graphics::ImageViewModel
{
    enum class Type {
        ImageView1D = VK_IMAGE_VIEW_TYPE_1D,
        ImageView2D = VK_IMAGE_VIEW_TYPE_2D,
        ImageView3D = VK_IMAGE_VIEW_TYPE_3D,
        ImageViewCube = VK_IMAGE_VIEW_TYPE_CUBE,
        ImageViewArray1D = VK_IMAGE_VIEW_TYPE_1D_ARRAY,
        ImageViewArray2D = VK_IMAGE_VIEW_TYPE_2D_ARRAY,
        ImageViewArrayCube = VK_IMAGE_VIEW_TYPE_CUBE_ARRAY
    };

    // Image related parameters
    Image               image {};
    Type                type {};
    VkFormat            format {};

    // Subregions parameters
    VkImageAspectFlags  apspectMasks {};
    uint32_t            mipMapIdx {};
    uint32_t            mipMapCount {};
    uint32_t            layerIdx {};
    uint32_t            layerCount {};
};