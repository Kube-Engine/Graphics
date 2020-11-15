/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Pipeline
 */

#pragma once

#include "VulkanHandle.hpp"
#include "PipelineModel.hpp"

namespace kF::Graphics
{
    class Pipeline;
}

/** @brief Abstraction of a GPU pipeline */
class kF::Graphics::Pipeline final : public VulkanHandle<PipelineHandle>
{
public:
    /** @brief Construct a pipeline using a model */
    Pipeline(const PipelineModel &model) { createPipeline(model); }

    /** @brief Move constructor */
    Pipeline(Pipeline &&other) noexcept = default;

    /** @brief Destruct the pipeline */
    ~Pipeline(void) noexcept;

    /** @brief Move assignment */
    Pipeline &operator=(Pipeline &&other) noexcept = default;

private:
    /** @brief Create a pipeline from model */
    void createPipeline(const PipelineModel &model);
};