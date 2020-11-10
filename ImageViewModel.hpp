/**
 * @ Author: Pierre Veysseyre
 * @ Description: ImageViewModel.hpp
 */

#pragma once

#include "Image.hpp"

namespace kF::Graphics
{
    struct ImageViewModel;
};

struct alignas_cacheline kF::Graphics::ImageViewModel
{
    enum class Type : VkImageViewType {
        ImageView1D = VK_IMAGE_VIEW_TYPE_1D,
        ImageView2D = VK_IMAGE_VIEW_TYPE_2D,
        ImageView3D = VK_IMAGE_VIEW_TYPE_3D,
        ImageViewCube = VK_IMAGE_VIEW_TYPE_CUBE,
        ImageViewArray1D = VK_IMAGE_VIEW_TYPE_1D_ARRAY,
        ImageViewArray2D = VK_IMAGE_VIEW_TYPE_2D_ARRAY,
        ImageViewArrayCube = VK_IMAGE_VIEW_TYPE_CUBE_ARRAY
    };

    ImageHandle image {};
    Type type {};
    VkFormat format {};
    VkImageAspectFlags apspectMasks {};
    uint32_t mipMapIdx { 0u };
    uint32_t mipMapCount { 0u };
    uint32_t layerIdx { 0u };
    uint32_t layerCount { 0u };
};

static_assert_cacheline(kF::Graphics::ImageViewModel);