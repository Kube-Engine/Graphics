/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: PipelineModel
 */

#pragma once

#include "ShaderStageModel.hpp"
#include "VertexInputModel.hpp"
#include "InputAssemblyModel.hpp"
#include "TessellationModel.hpp"
#include "ViewportModel.hpp"
#include "RasterizationModel.hpp"
#include "MultisampleModel.hpp"
#include "DepthStencilModel.hpp"
#include "ColorBlendModel.hpp"
#include "DynamicStateModel.hpp"

namespace kF::Graphics
{
    struct PipelineModel;
};

/** @brief Describe how to create a sampler */
struct kF::Graphics::PipelineModel : public VkGraphicsPipelineCreateInfo
{
    /** @brief Initialize constructor */
    PipelineModel(const PipelineCreateFlags flags_,
            const ShaderStageModel * const stageBegin, const ShaderStageModel * const stageEnd,
            const VertexInputModel * const pVertexInputState_,
            const InputAssemblyModel * const pInputAssemblyState_,
            const TessellationModel * const pTessellationState_,
            const ViewportModel * const pViewportState_,
            const RasterizationModel * const pRasterizationState_,
            const MultisampleModel * const pMultisampleState_,
            const DepthStencilModel * const pDepthStencilState_,
            const ColorBlendModel * const pColorBlendState_,
            const DynamicStateModel * const pDynamicState_,
            const PipelineLayoutHandle layout_,
            const RenderPassHandle renderPass_, const std::uint32_t subpass_,
            const PipelineHandle basePipelineHandle_, const std::int32_t basePipelineIndex_)
        noexcept
        : VkGraphicsPipelineCreateInfo {
            sType: VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
            pNext: nullptr,
            flags: ToFlags(flags_),
            stageCount: static_cast<std::uint32_t>(std::distance(stageBegin, stageEnd)),
            pStages: stageBegin,
            pVertexInputState: pVertexInputState_,
            pInputAssemblyState: pInputAssemblyState_,
            pTessellationState: pTessellationState_,
            pViewportState: pViewportState_,
            pRasterizationState: pRasterizationState_,
            pMultisampleState: pMultisampleState_,
            pDepthStencilState: pDepthStencilState_,
            pColorBlendState: pColorBlendState_,
            pDynamicState: pDynamicState_,
            layout: layout_,
            renderPass: renderPass_,
            subpass: subpass_,
            basePipelineHandle: basePipelineHandle_,
            basePipelineIndex: basePipelineIndex_
        } {}

    /** @brief POD semantics */
    PipelineModel(const PipelineModel &other) noexcept = default;
    PipelineModel(PipelineModel &&other) noexcept = default;
    PipelineModel &operator=(const PipelineModel &other) noexcept = default;
    PipelineModel &operator=(PipelineModel &&other) noexcept = default;
};
