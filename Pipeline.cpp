/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Pipeline
 */

#include <Kube/Core/StringLiteral.hpp>

#include "Renderer.hpp"
#include "Pipeline.hpp"

using namespace kF;
using namespace kF::Literal;

Graphics::Pipeline::~Pipeline(void) noexcept
{
    ::vkDestroyPipeline(parent().logicalDevice(), handle(), nullptr);
}

void Graphics::Pipeline::createPipeline(const PipelineModel &model)
{
    auto shaderStage = getShaderStage(model);
    auto inputStage = getInputStage(model);
    auto outputStage = getOutputStage(model);
    auto multisampleStage = getMultisampleStage(model);
    auto colorStage = getColorStage(model);
    auto dynamicStage = getDynamicStage(model);

    VkGraphicsPipelineCreateInfo pipelineInfo {
        sType: VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        pNext: nullptr,
        flags: VkPipelineCreateFlags(),
        stageCount: static_cast<std::uint32_t>(shaderStage.shaderInfos.size()),
        pStages: shaderStage.shaderInfos.data(),
        pVertexInputState: &inputStage.vertexInfo,
        pInputAssemblyState: &inputStage.assemblyInfo,
        pTessellationState: nullptr,
        pViewportState: &outputStage.viewportInfo,
        pRasterizationState: &outputStage.rasterizerInfo,
        pMultisampleState: &multisampleStage.multisampleInfo,
        pDepthStencilState: nullptr,
        pColorBlendState: &colorStage.colorBlendInfo,
        pDynamicState: &dynamicStage.dynamicStatesInfo,
        layout: _pipelineLayout,
        renderPass: parent().renderPass(),
        subpass: 0,
        basePipelineHandle: nullptr,
        basePipelineIndex: -1
    };

    if (auto res = ::vkCreateGraphicsPipelines(parent().logicalDevice(), VkPipelineCache(), 1, &pipelineInfo, nullptr, &handle()); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::Pipeline::createPipeline: Couldn't create pipeline '"s + ErrorMessage(res) + '\'');
}

Graphics::Pipeline::ShaderStage Graphics::Pipeline::getShaderStage(const PipelineModel &model) const
{
    ShaderStage stage;
    auto max = model.shaders.size();

    stage.shaderInfos.resize(max, VkPipelineShaderStageCreateInfo {
        sType: VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        pNext: nullptr,
        flags: VkPipelineShaderStageCreateFlags(),
        stage: VkShaderStageFlagBits(),
        module: VkShaderModule(),
        pName: "main",
        pSpecializationInfo: nullptr
    });
    for (auto i = 0u; i < max; ++i) {
        auto &shaderModel = model.shaders[i];
        auto &shader = stage.shaders.emplace_back(parent(), shaderModel.path);
        auto &shaderInfo = stage.shaderInfos[i];
        shaderInfo.stage = static_cast<VkShaderStageFlagBits>(shaderModel.type);
        shaderInfo.module = shader;
    }
    return stage;
}

Graphics::Pipeline::InputStage Graphics::Pipeline::getInputStage(const PipelineModel &model) const noexcept
{
    return InputStage {
        VkPipelineVertexInputStateCreateInfo {
            sType: VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
            pNext: nullptr,
            flags: VkPipelineVertexInputStateCreateFlags(),
            vertexBindingDescriptionCount: static_cast<std::uint32_t>(model.layoutModel.bindings.size()),
            pVertexBindingDescriptions: model.layoutModel.bindings.data(),
            vertexAttributeDescriptionCount: static_cast<std::uint32_t>(model.layoutModel.attributes.size()),
            pVertexAttributeDescriptions: model.layoutModel.attributes.data()
        },
        VkPipelineInputAssemblyStateCreateInfo {
            sType: VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
            pNext: nullptr,
            flags: VkPipelineInputAssemblyStateCreateFlags(),
            topology: VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
            primitiveRestartEnable: false
        }
    };
}

Graphics::Pipeline::OutputStage Graphics::Pipeline::getOutputStage(const PipelineModel &model) const noexcept
{
    OutputStage stage {
        VkViewport {
            x: 0.0f,
            y: 0.0f,
            width: static_cast<float>(parent().swapchain().extent().width),
            height: static_cast<float>(parent().swapchain().extent().height),
            minDepth: 0.0f,
            maxDepth: 1.0f
        },
        VkRect2D {
            { 0, 0 },
            { parent().swapchain().extent().width, parent().swapchain().extent().height }
        },
        VkPipelineViewportStateCreateInfo {
            sType: VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
            pNext: nullptr,
            flags: VkPipelineViewportStateCreateFlags(),
            viewportCount: 1,
            pViewports: &stage.viewport,
            scissorCount: 1,
            pScissors: &stage.scissor
        },
        VkPipelineRasterizationStateCreateInfo {
            sType: VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
            pNext: nullptr,
            flags: VkPipelineRasterizationStateCreateFlags(),
            depthClampEnable: false,
            rasterizerDiscardEnable: false,
            polygonMode: VK_POLYGON_MODE_FILL,
            cullMode: VK_CULL_MODE_BACK_BIT,
            frontFace: VK_FRONT_FACE_CLOCKWISE,
            depthBiasEnable: false,
            depthBiasConstantFactor: 0.0f,
            depthBiasClamp: 0.0f,
            depthBiasSlopeFactor: 0.0f,
            lineWidth: 1.0f
        }
    };

    return stage;
}

Graphics::Pipeline::MultisampleStage Graphics::Pipeline::getMultisampleStage(const PipelineModel &model) const noexcept
{
    return MultisampleStage {
        VkPipelineMultisampleStateCreateInfo {
            sType: VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
            pNext: nullptr,
            flags: VkPipelineMultisampleStateCreateFlags(),
            rasterizationSamples: VK_SAMPLE_COUNT_1_BIT,
            sampleShadingEnable: false,
            minSampleShading: 1.0f,
            pSampleMask: nullptr,
            alphaToCoverageEnable: false,
            alphaToOneEnable: false
        }
    };
}

Graphics::Pipeline::ColorStage Graphics::Pipeline::getColorStage(const PipelineModel &model) const noexcept
{
    ColorStage stage {
        VkPipelineColorBlendAttachmentState {
            blendEnable: true,
            srcColorBlendFactor: VK_BLEND_FACTOR_SRC_ALPHA,
            dstColorBlendFactor: VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
            colorBlendOp: VK_BLEND_OP_ADD,
            srcAlphaBlendFactor: VK_BLEND_FACTOR_ONE,
            dstAlphaBlendFactor: VK_BLEND_FACTOR_ZERO,
            alphaBlendOp: VK_BLEND_OP_ADD,
            colorWriteMask: VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT
        },
        VkPipelineColorBlendStateCreateInfo {
            sType: VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
            pNext: nullptr,
            flags: VkPipelineColorBlendStateCreateFlags(),
            logicOpEnable: false,
            logicOp: VK_LOGIC_OP_COPY,
            attachmentCount: 1,
            pAttachments: &stage.colorBlend,
            blendConstants: { 0, 0, 0, 0 }
        }
    };

    return stage;
}

Graphics::Pipeline::DynamicStage Graphics::Pipeline::getDynamicStage(const PipelineModel &model) const noexcept
{
    DynamicStage stage {
        {
            //VK_DYNAMIC_STATE_VIEWPORT
        },
        VkPipelineDynamicStateCreateInfo {
            sType: VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
            pNext: nullptr,
            flags: VkPipelineDynamicStateCreateFlags(),
            dynamicStateCount: static_cast<std::uint32_t>(stage.dynamicStates.size()),
            pDynamicStates: stage.dynamicStates.data()
        }
    };

    return stage;
}
