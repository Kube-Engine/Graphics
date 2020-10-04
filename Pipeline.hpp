/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Pipeline
 */

#pragma once

#include "VulkanHandler.hpp"
#include "Shader.hpp"
#include "LayoutModel.hpp"

namespace kF::Graphics
{
    class Pipeline;
    struct PipelineModel;

    /** @brief A vulkan pipeline layout */
    using PipelineLayout = VkPipelineLayout;
}

/** @brief Describes how to create a pipeline */
struct kF::Graphics::PipelineModel
{
    ShaderModels shaders;
    LayoutModel layoutModel;
};

/** @brief Abstraction of a GPU pipeline */
class kF::Graphics::Pipeline final : public VulkanHandler<VkPipeline>
{
public:
    /** @brief Various stages structures used to setup the pipeline */
    struct ShaderStage;
    struct InputStage;
    struct OutputStage;
    struct MultisampleStage;
    struct ColorStage;
    struct DynamicStage;
    struct LayoutStage;

    /** @brief Construct a pipeline using a model */
    Pipeline(Renderer &renderer, const PipelineModel &model);

    /** @brief Move constructor */
    Pipeline(Pipeline &&other) noexcept : VulkanHandler<VkPipeline>(other.parent()) { swap(other); }

    /** @brief Destruct the pipeline */
    ~Pipeline(void);

    /** @brief Move assignment */
    Pipeline &operator=(Pipeline &&other) noexcept { swap(other); return *this; }

    /** @brief Get the pipeline layout */
    [[nodiscard]] PipelineLayout &getPipelineLayout(void) noexcept { return _pipelineLayout; }
    [[nodiscard]] const PipelineLayout &getPipelineLayout(void) const noexcept { return _pipelineLayout; }

    /** @brief Swap two instances */
    void swap(Pipeline &other) noexcept;

private:
    PipelineLayout _pipelineLayout = VK_NULL_HANDLE;

    /** @brief Create a pipeline layout */
    void createPipelineLayout(const PipelineModel &model);

    /** @brief Create a pipeline */
    void createPipeline(const PipelineModel &model);

    /** @brief Build shader stage from model */
    [[nodiscard]] ShaderStage getShaderStage(const PipelineModel &model) const;

    /** @brief Build input stage from model */
    [[nodiscard]] InputStage getInputStage(const PipelineModel &model) const noexcept;

    /** @brief Build output stage from model */
    [[nodiscard]] OutputStage getOutputStage(const PipelineModel &model) const noexcept;

    /** @brief Build multisample stage from model */
    [[nodiscard]] MultisampleStage getMultisampleStage(const PipelineModel &model) const noexcept;

    /** @brief Build color stage from model */
    [[nodiscard]] ColorStage getColorStage(const PipelineModel &model) const noexcept;

    /** @brief Build dynamic stage from model */
    [[nodiscard]] DynamicStage getDynamicStage(const PipelineModel &model) const noexcept;
};

/** @brief Describes shader stage of the pipeline */
struct kF::Graphics::Pipeline::ShaderStage
{
    std::vector<VkPipelineShaderStageCreateInfo> shaderInfos;
    std::vector<Shader> shaders;
};

/** @brief Describes input stage of the pipeline */
struct kF::Graphics::Pipeline::InputStage
{
    VkPipelineVertexInputStateCreateInfo vertexInfo;
    VkPipelineInputAssemblyStateCreateInfo assemblyInfo;
};

/** @brief Describes output stage of the pipeline */
struct kF::Graphics::Pipeline::OutputStage
{
    VkViewport viewport;
    VkRect2D scissor;
    VkPipelineViewportStateCreateInfo viewportInfo;
    VkPipelineRasterizationStateCreateInfo rasterizerInfo;
};

/** @brief Describes multisample stage of the pipeline */
struct kF::Graphics::Pipeline::MultisampleStage
{
    VkPipelineMultisampleStateCreateInfo multisampleInfo;
};

/** @brief Describes color stage of the pipeline */
struct kF::Graphics::Pipeline::ColorStage
{
    VkPipelineColorBlendAttachmentState colorBlend;
    VkPipelineColorBlendStateCreateInfo colorBlendInfo;
};

/** @brief Describes dynamic stage of the pipeline */
struct kF::Graphics::Pipeline::DynamicStage
{
    std::vector<VkDynamicState> dynamicStates;
    VkPipelineDynamicStateCreateInfo dynamicStatesInfo;
};
