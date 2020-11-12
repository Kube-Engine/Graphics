/**
 * @ Author: Pierre Veysseyre
 * @ Description: SamplerModel
 */

#pragma once

#include "Vulkan.hpp"

namespace kF::Graphics
{
    struct SamplerModel;
};

/** @brief Describe how to create a sampler */
struct kF::Graphics::SamplerModel : public VkSamplerCreateInfo
{
    /** @brief Initialize constructor */
    SamplerModel(const SamplerCreateFlags flags_, const Filter magFilter_, const Filter minFilter_,
            const VkSamplerMipmapMode mipmapMode_, const SamplerAddressMode addressModeU_,
            const SamplerAddressMode addressModeV_, const SamplerAddressMode addressModeW_,
            const float mipLodBias_,const bool anisotropyEnable_, const float maxAnisotropy_,
            const bool compareEnable_, const CompareOp compareOp_,
            const float minLod_, const float maxLod_,
            const BorderColor borderColor_, const bool unnormalizedCoordinates_)
        noexcept
        : VkSamplerCreateInfo {
            sType: VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
            pNext: nullptr,
            flags: flags_,
            magFilter: magFilter_,
            minFilter: minFilter_,
            mipmapMode: mipmapMode_,
            addressModeU: addressModeU_,
            addressModeV: addressModeV_,
            addressModeW: addressModeW_,
            mipLodBias: mipLodBias_,
            anisotropyEnable: anisotropyEnable_,
            maxAnisotropy: maxAnisotropy_,
            compareEnable: compareEnable_,
            compareOp: compareOp_,
            minLod: minLod_,
            maxLod: maxLod_,
            borderColor: borderColor_,
            unnormalizedCoordinates: unnormalizedCoordinates_
        } {}

    /** @brief POD semantics */
    SamplerModel(const SamplerModel &other) noexcept = default;
    SamplerModel(SamplerModel &&other) noexcept = default;
    SamplerModel &operator=(const SamplerModel &other) noexcept = default;
    SamplerModel &operator=(SamplerModel &&other) noexcept = default;
};
