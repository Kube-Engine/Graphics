/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: PipelineManager
 */

#pragma once

#include <memory>

#include <Kube/Core/Assert.hpp>

#include "Pipeline.hpp"

namespace kF::Graphics
{
    class PipelineManager;
}

/** @brief Abstraction of a pipeline pool */
class kF::Graphics::PipelineManager final : public RendererObject
{
public:
    /** @brief Construct a pool of pipelines */
    PipelineManager(Renderer &renderer) : RendererObject(renderer) {}

    /** @brief Move constructor */
    PipelineManager(PipelineManager &&other) noexcept = default;

    /** @brief Destruct the pipeline pool */
    ~PipelineManager(void) noexcept = default;

    /** @brief Move assignment */
    PipelineManager &operator=(PipelineManager &&other) noexcept = default;


    /** @brief Add a pipeline to the pool using a model */
    [[nodiscard]] PipelineHandle add(const PipelineModel &model);

    /** @brief Remove a pipeline from the pool using its index */
    void remove(const PipelineHandle pipeline) noexcept_ndebug;


    /** @brief Callback on render view size changed */
    void onViewSizeChanged(void);

private:
    Core::TinyVector<Pipeline> _pipelines;
    Core::TinyVector<std::unique_ptr<PipelineModel>> _models;
};
