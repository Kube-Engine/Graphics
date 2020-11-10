/**
 * @ Author: Pierre Veysseyre
 * @ Description: ImageViewModel.hpp
 */

#pragma once

#include "Image.hpp"

namespace kF::Graphics
{
    struct ImageViewModel;

    /** @brief Creation flags of image views */
    using ImageViewCreateFlags = VkImageViewCreateFlagBits;

    /** @brief Types of image views */
    using ImageViewType = VkImageViewType;

    /** @brief Image subresource range */
    using ImageSubresourceRange = VkImageSubresourceRange;

    /** @brief Image aspect flags */
    using ImageAspectFlags = VkImageAspectFlagBits;
};

struct alignas_cacheline kF::Graphics::ImageViewModel
{
    ImageViewCreateFlags flags {};
    ImageHandle image {};
    ImageViewType viewType {};
    Format format {};
    ImageSubresourceRange subresourceRange {};
};

static_assert_cacheline(kF::Graphics::ImageViewModel);