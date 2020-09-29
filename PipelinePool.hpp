/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: PipelinePool
 */

#pragma once

#include <vector>
#include <memory>

#include "Pipeline.hpp"

namespace kF
{
    class PipelinePool;

    using PipelineIndex = std::uint32_t;
}

class kF::PipelinePool final : public RendererObject
{
public:
    using PipelinePair = std::pair<PipelineIndex, std::unique_ptr<Pipeline>>;
    using PipelineModelPair = std::pair<PipelineIndex, std::unique_ptr<PipelineModel>>;
    using PipelineMap = std::vector<PipelinePair>;
    using PipelineModelMap = std::vector<PipelineModelPair>;

    PipelinePool(Renderer &renderer);
    PipelinePool(PipelinePool &&other) = default;
    ~PipelinePool(void) = default;

    PipelinePool &operator=(PipelinePool &&other) = default;

    [[nodiscard]] PipelineIndex addPipeline(const PipelineModel &model);
    void removePipeline(const PipelineIndex index);

    [[nodiscard]] Pipeline &getPipeline(const PipelineIndex index);
    [[nodiscard]] const Pipeline &getPipeline(const PipelineIndex index) const;

    void onViewSizeChanged(void);

private:
    PipelineMap _pipelineMap;
#ifdef KUBE_NO_DYNAMIC_RESIZE
    PipelineModelMap _modelMap;
#endif

    auto findPipeline(const PipelineIndex index) noexcept { return std::find_if(_pipelineMap.begin(), _pipelineMap.end(), [index](const auto &pair) { return pair.first == index; }); }
    auto findPipeline(const PipelineIndex index) const noexcept { return std::find_if(_pipelineMap.begin(), _pipelineMap.end(), [index](const auto &pair) { return pair.first == index; }); }
};