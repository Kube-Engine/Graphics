/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Pipeline
 */

inline kF::Graphics::Pipeline::Pipeline(Renderer &renderer, const PipelineModel &model)
    : VulkanHandler<PipelineHandle>(renderer), _pipelineLayout(renderer, model.layout)
{
    createPipeline(model);
}

inline void kF::Graphics::Pipeline::swap(Pipeline &other) noexcept
{
    VulkanHandler<VkPipeline>::swap(other);
    std::swap(_pipelineLayout, other._pipelineLayout);
}