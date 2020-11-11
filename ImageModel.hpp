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
    ImageModel(const ImageCreateFlags flags_, const ImageType type_, const Format format_, const Extent3D &extent_,
            const std::uint32_t mipLevels_, const std::uint32_t arrayLayers_, const SampleCountFlags samples_,
            const ImageTiling tiling_, const ImageUsageFlags usage_, const SharingMode sharingMode_,
            const uint32_t queueFamilyIndexCount_, const uint32_t *pQueueFamilyIndices_, const ImageLayout initialLayout_)
        noexcept
        : VkImageCreateInfo(
            sType: VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
            pNext: nullptr,
            flags: flags_,
            imageType: type_,
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

    [[nodiscard]] static ImageModel MakeBasicImage(const ImageType type, const Extent3D &extent, const Format format, const SampleCountFlags samples)
        noexcept {
        return ImageModel(
            ImageCreateFlags::None,
            type,
            format,
            Extent3D {
                width: extent.width,
                height: (type != ImageType::Type1D ? extent.height : 1),
                depth: (type == ImageType::Type3D ? extent.depth : 1)
            },
            1,
            1,
            samples,
            ImageTiling::TilingOptimal,
            ImageUsageFlags::TransferDstBit | ImageUsageFlags::SampledBit,
            SharingMode::Exclusive,
            0,
            nullptr,
            ImageLayout::Undefined,
        );
    }

    // [[nodiscard]] static ImageModel MakeBasic2D(const Extent3D &extent, const Format format, const SampleCountFlags samples) noexcept {
    //     return ImageModel(
    //         0,
    //         ImageType::Type2D,
    //         format,
    //         Extent3D {
    //             width: extent.width,
    //             height: extent.height,
    //             depth: 1
    //         },
    //         1,
    //         1,
    //         samples,
    //         ImageTiling::TilingOptimal,
    //         ImageUsageFlags::TransferBit | ImageUsageFlags::SampledBit,
    //         SharingMode::Exclusive,
    //         0,
    //         nullptr,
    //         ImageLayout::Undefined
    //     );
    // }

    // [[nodiscard]] static ImageModel MakeBasic3D(const Extent3D &extent, const Format format, const SampleCountFlags samples) noexcept {
    //     return ImageModel(
    //         0,
    //         ImageType::Type3D,
    //         format,
    //         extent,
    //         1,
    //         1,
    //         samples,
    //         ImageTiling::TilingOptimal,
    //         ImageUsageFlags::TransferBit | ImageUsageFlags::SampledBit,
    //         SharingMode::Exclusive,
    //         0,
    //         nullptr,
    //         ImageLayout::Undefined
    //     );
    // }

    [[nodiscard]] static ImageModel MakeLayerImage(const ImageType type, const Extent3D &extent, const Format format, const SampleCountFlags samples, const uint32_t layers) noexcept {
        return ImageModel(
            ImageCreateFlags::None,
            ImageType::Type2D,
            format,
            Extent3D {
                width: extent.width,
                height: (type != ImageType::Type1D ? extent.height : 1),
                depth: (type == ImageType::Type3D ? extent.depth : 1)
            },
            layers ? layers : 1,
            1,
            samples,
            ImageTiling::TilingOptimal,
            ImageUsageFlags::TransferBit | ImageUsageFlags::SampledBit,
            SharingMode::Exclusive,
            0,
            nullptr,
            ImageLayout::Undefined
        );
    }

    [[nodiscard]] static ImageModel MakeMipMapImage(const ImageType type, const Extent3D &extent, const Format format, const SampleCountFlags samples, const uint32_t mipLevels) noexcept {
        return ImageModel(
            ImageCreateFlags::None,
            ImageType::Type2D,
            format,
            Extent3D {
                width: extent.width,
                height: (type != ImageType::Type1D ? extent.height : 1),
                depth: (type == ImageType::Type3D ? extent.depth : 1)
            },
            1,
            mipLevels ? mipLevels : 1,
            samples,
            ImageTiling::TilingOptimal,
            ImageUsageFlags::TransferBit | ImageUsageFlags::SampledBit,
            SharingMode::Exclusive,
            0,
            nullptr,
            ImageLayout::Undefined
        );
    }

};
