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
class kF::Graphics::PipelineManager final : public CachedRendererObject
{
public:
    /** @brief Construct a pool of pipelines */
    PipelineManager(void) noexcept = default;

    /** @brief Move constructor */
    PipelineManager(PipelineManager &&other) noexcept = default;

    /** @brief Destruct the pipeline pool */
    ~PipelineManager(void) noexcept = default;

    /** @brief Move assignment */
    PipelineManager &operator=(PipelineManager &&other) noexcept = default;


    /** @brief Add a pipeline to the pool using a model */
    [[nodiscard]] PipelineHandle add(const PipelineModel &model);

    /** @brief Remove a pipeline from the pool using its handle */
    void remove(const PipelineHandle pipeline) noexcept_ndebug;

    /** @brief Remove every pipeline from the pool */
    void clear(void) noexcept { _pipelines.clear(); }


    /** @brief Callback on render view size changed */
    void onViewSizeChanged(void) { clear(); }

private:
    Core::TinyVector<Pipeline> _pipelines;
};
