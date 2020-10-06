/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: PipelinePool
 */

#pragma once

#include <vector>
#include <memory>

#include "Pipeline.hpp"

namespace kF::Graphics
{
    class PipelinePool;

    /** @brief Index of a pipeline in the pool */
    using PipelineIndex = std::uint32_t;
}

/** @brief Abstraction of a pipeline pool */
class kF::Graphics::PipelinePool final : public RendererObject
{
public:
    /** @brief A pair containing a pipeline index and its instance */
    using PipelinePair = std::pair<PipelineIndex, std::unique_ptr<Pipeline>>;

    /** @brief A pair containing a pipeline index and its model */
    using PipelineModelPair = std::pair<PipelineIndex, std::unique_ptr<PipelineModel>>;

    /** @brief A map of pipelines indexes and instances */
    using PipelineMap = std::vector<PipelinePair>;

    /** @brief A map of pipelines indexes and models */
    using PipelineModelMap = std::vector<PipelineModelPair>;

    /** @brief Construct a pool of pipelines */
    PipelinePool(Renderer &renderer);

    /** @brief Move constructor */
    PipelinePool(PipelinePool &&other) noexcept = default;

    /** @brief Destruct the pipeline pool */
    ~PipelinePool(void) = default;

    /** @brief Move assignment */
    PipelinePool &operator=(PipelinePool &&other) noexcept = default;

    /** @brief Add a pipeline to the pool using a model
     *  @return The pipeline index */
    [[nodiscard]] PipelineIndex addPipeline(const PipelineModel &model);

    /** @brief Remove a pipeline from the pool using its index */
    void removePipeline(const PipelineIndex index);

    /** @brief Get a pipeline from the pool using its index */
    [[nodiscard]] Pipeline &getPipeline(const PipelineIndex index);
    [[nodiscard]] const Pipeline &getPipeline(const PipelineIndex index) const;

    /** @brief Callback on render view size changed */
    void onViewSizeChanged(void);

private:
    PipelineMap _pipelineMap;
#ifndef KUBE_HAS_DYNAMIC_WINDOW_RESIZE
    PipelineModelMap _modelMap;
#endif

    /** @brief Find a pipeline in the pool using its index */
    auto findPipeline(const PipelineIndex index) noexcept { return std::find_if(_pipelineMap.begin(), _pipelineMap.end(), [index](const auto &pair) { return pair.first == index; }); }
    auto findPipeline(const PipelineIndex index) const noexcept { return std::find_if(_pipelineMap.begin(), _pipelineMap.end(), [index](const auto &pair) { return pair.first == index; }); }
};