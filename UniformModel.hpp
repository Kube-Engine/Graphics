/**
 * @ Author: Pierre Veysseyre
 * @ Description: UniformModel.hpp
 */

#pragma once

#include "Vulkan.hpp"

namespace kF::Graphics
{
    struct UniformModel;
};

/** @brief Describe how to create an image */
struct kF::Graphics::UniformModel : public VkUniformCreateInfo
{
    /** @brief Initialize constructor */
    UniformModel(const ImageCreateFlags flags_, const ImageType type_, const Format format_, const Extent3D &extent_,
            const std::uint32_t mipLevels_, const std::uint32_t arrayLayers_, const SampleCountFlags samples_,
            const ImageTiling tiling_, const ImageUsageFlags usage_, const SharingMode sharingMode_,
            const std::uint32_t * const queueFamilyIndexBegin, const std::uint32_t * const queueFamilyIndexEnd,
            const ImageLayout initialLayout_)
        noexcept
        : VkImageCreateInfo {
            sType: VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
            pNext: nullptr,
            flags: ToFlags(flags_),
            imageType: static_cast<VkImageType>(type_),
            format: static_cast<VkFormat>(format_),
            extent: extent_,
            mipLevels: mipLevels_,
            arrayLayers: arrayLayers_,
            samples: static_cast<VkSampleCountFlagBits>(samples_),
            tiling: static_cast<VkImageTiling>(tiling_),
            usage: ToFlags(usage_),
            sharingMode: static_cast<VkSharingMode>(sharingMode_),
            queueFamilyIndexCount: static_cast<std::uint32_t>(std::distance(queueFamilyIndexBegin, queueFamilyIndexEnd)),
            pQueueFamilyIndices: queueFamilyIndexBegin,
            initialLayout: static_cast<VkImageLayout>(initialLayout_)
         } {}

    /** @brief POD semantics */
    UniformModel(const UniformModel &other) noexcept = default;
    UniformModel(UniformModel &&other) noexcept = default;
    UniformModel &operator=(const UniformModel &other) noexcept = default;
    UniformModel &operator=(UniformModel &&other) noexcept = default;

};
