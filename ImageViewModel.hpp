/**
 * @ Author: Pierre Veysseyre
 * @ Description: ImageViewModel.hpp
 */

#pragma once

#include "Image.hpp"

namespace kF::Graphics
{
    struct ImageViewModel;

    /** @brief Image subresource range */
    using ImageSubresourceRange = VkImageSubresourceRange;

    /** @brief Component mapping */
    using ComponentMapping = VkComponentMapping;
};

struct kF::Graphics::ImageViewModel : public VkImageViewCreateInfo
{
    /** @brief Initialize constructor */
    ImageViewModel(const Image &image_, const ImageViewCreateFlags flags_, const ImageViewType type_, const Format format_,
            const ImageSubresourceRange &subresource_, const ComponentMapping &component_)
        noexcept
        : VkImageViewCreateInfo(
            sType: VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            pNext: nullptr,
            image: image_,
            flags: flags_,
            viewType: type,
            format: format_,
            components: component_,
            subresourceRange: subresource_
        ) {}

        /** @brief POD semantics */
    ImageViewModel(const ImageViewModel &other) noexcept = default;
    ImageViewModel(ImageViewModel &&other) noexcept = default;
    ImageViewModel &operator=(const ImageViewModel &other) noexcept = default;
    ImageViewModel &operator=(ImageViewModel &&other) noexcept = default;

};

// struct alignas_cacheline kF::Graphics::ImageViewModel
// {
//     ImageViewCreateFlags flags {};
//     ImageHandle image {};
//     ImageViewType viewType {};
//     Format format {};
//     ImageSubresourceRange subresourceRange {};
// };

// static_assert_cacheline(kF::Graphics::ImageViewModel);