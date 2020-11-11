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

struct kF::Graphics::ImageModel : public VkImageCreateInfo
{
    /** @brief Initialize constructor */
    ImageModel(const ImageCreateFlags flags_, const ImageType imageType_, const Format format_, const Extent3D &extent_,
            const std::uint32_t mipLevels_, const std::uint32_t arrayLayers_, const SampleCountFlags samples_,
            const ImageTiling tiling_, const Usage usage_, const SharingMode sharingMode_) noexcept
        : VkImageCreateInfo(
            sType: VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
            pNext: nullptr,
            flags: createFlags_,
            imageType: imageType_,
            format: format_,
            extent: extent_,
            mipLevels: mipLevels_,
            arrayLayers: arrayLayers_,
            samples: samples_,
            tiling: tiling_,
            usage: usage_,
            sharingMode: sharingMode_,
            queueFamilyIndexCount: queueFamilyIndexCount_,
            pQueueFamilyIndices: pQueueFamilyIndices_,
            initialLayout: initialLayout_
        ) {}

    /** @brief POD semantics */
    ImageModel(const ImageModel &other) noexcept = default;
    ImageModel(ImageModel &&other) noexcept = default;
    ImageModel &operator=(const ImageModel &other) noexcept = default;
    ImageModel &operator=(ImageModel &&other) noexcept = default;
};
