/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Pipeline
 */

#include "VulkanHandler.hpp"
#include "Shader.hpp"
#include "LayoutModel.hpp"

namespace kF
{
    class Pipeline;
    struct PipelineModel;

    using PipelineLayout = VkPipelineLayout;
}

struct kF::PipelineModel
{
    ShaderModels shaders;
    LayoutModel layoutModel;
};

class kF::Pipeline final : public VulkanHandler<VkPipeline>
{
public:
    struct ShaderStage;
    struct InputStage;
    struct OutputStage;
    struct MultisampleStage;
    struct ColorStage;
    struct DynamicStage;
    struct LayoutStage;

    Pipeline(Renderer &renderer, const PipelineModel &model);
    Pipeline(Pipeline &&other) : VulkanHandler<VkPipeline>(other.parent()) { swap(other); }
    ~Pipeline(void);

    Pipeline &operator=(Pipeline &&other) { swap(other); return *this; }

    [[nodiscard]] PipelineLayout &getPipelineLayout(void) noexcept { return _pipelineLayout; }
    [[nodiscard]] const PipelineLayout &getPipelineLayout(void) const noexcept { return _pipelineLayout; }

    void swap(Pipeline &other) noexcept;

private:
    PipelineLayout _pipelineLayout = VK_NULL_HANDLE;

    void createPipelineLayout(const PipelineModel &model);
    void createPipeline(const PipelineModel &model);

    ShaderStage getShaderStage(const PipelineModel &model);
    InputStage getInputStage(const PipelineModel &model) const;
    OutputStage getOutputStage(const PipelineModel &model) const;
    MultisampleStage getMultisampleStage(const PipelineModel &model) const;
    ColorStage getColorStage(const PipelineModel &model) const;
    DynamicStage getDynamicStage(const PipelineModel &model) const;
};

struct kF::Pipeline::ShaderStage
{
    std::vector<VkPipelineShaderStageCreateInfo> shaderInfos;
    std::vector<Shader> shaders;
};

struct kF::Pipeline::InputStage
{
    VkPipelineVertexInputStateCreateInfo vertexInfo;
    VkPipelineInputAssemblyStateCreateInfo assemblyInfo;
};

struct kF::Pipeline::OutputStage
{
    VkViewport viewport;
    VkRect2D scissor;
    VkPipelineViewportStateCreateInfo viewportInfo;
    VkPipelineRasterizationStateCreateInfo rasterizerInfo;
};

struct kF::Pipeline::MultisampleStage
{
    VkPipelineMultisampleStateCreateInfo multisampleInfo;
};

struct kF::Pipeline::ColorStage
{
    VkPipelineColorBlendAttachmentState colorBlend;
    VkPipelineColorBlendStateCreateInfo colorBlendInfo;
};

struct kF::Pipeline::DynamicStage
{
    std::vector<VkDynamicState> dynamicStates;
    VkPipelineDynamicStateCreateInfo dynamicStatesInfo;
};
