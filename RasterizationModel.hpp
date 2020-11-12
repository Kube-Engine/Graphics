/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: RasterizationModel
 */

#pragma once

#include "Vulkan.hpp"

namespace kF::Graphics
{
    struct RasterizationModel;
};

/** @brief Describe how to create a sampler */
struct kF::Graphics::RasterizationModel : public VkPipelineRasterizationStateCreateInfo
{
    /** @brief Initialize constructor */
    RasterizationModel(const RasterizationCreateFlags flags_, const bool depthClampEnable_, const bool rasterizerDiscardEnable_,
            const PolygonMode polygonMode_, const CullModeFlags cullMode_, const FrontFace frontFace_, const bool depthBiasEnable_,
            const float depthBiasConstantFactor_, const float depthBiasClamp_,const float depthBiasSlopeFactor_, const float lineWidth_)
        noexcept
        : VkPipelineRasterizationStateCreateInfo {
            sType: VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
            pNext: nullptr,
            flags: ToFlags(flags_),
            depthClampEnable: depthClampEnable_,
            rasterizerDiscardEnable: rasterizerDiscardEnable_,
            polygonMode: static_cast<VkPolygonMode>(polygonMode_),
            cullMode: ToFlags(cullMode_),
            frontFace: static_cast<VkFrontFace>(frontFace_),
            depthBiasEnable: depthBiasEnable_,
            depthBiasConstantFactor: depthBiasConstantFactor_,
            depthBiasClamp: depthBiasClamp_,
            depthBiasSlopeFactor: depthBiasSlopeFactor_,
            lineWidth: lineWidth_
        } {}

    /** @brief POD semantics */
    RasterizationModel(const RasterizationModel &other) noexcept = default;
    RasterizationModel(RasterizationModel &&other) noexcept = default;
    RasterizationModel &operator=(const RasterizationModel &other) noexcept = default;
    RasterizationModel &operator=(RasterizationModel &&other) noexcept = default;
};
