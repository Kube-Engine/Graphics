/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: PipelineLayout
 */

#pragma once

#include "PipelineLayoutModel.hpp"

namespace kF::Graphics
{
    class PipelineLayout;

    /** @brief A device pipeline layout */
    using PipelineLayoutHandle = VkPipelineLayout;
}

class kF::Graphics::PipelineLayout : public VulkanHandler<PipelineLayoutHandle>
{
public:
    /** @brief Construct a pipeline using a model */
    PipelineLayout(Renderer &renderer, const PipelineLayoutModel &model)
        : VulkanHandler<PipelineLayoutHandle>(renderer) { createPipelineLayout(model); }

    /** @brief Move constructor */
    PipelineLayout(PipelineLayout &&other) noexcept = default;

    /** @brief Destruct the pipelineLayout */
    ~PipelineLayout(void);

    /** @brief Move assignment */
    PipelineLayout &operator=(Pipeline &&other) noexcept = default;

private:
    /** @brief Create a pipeline layout from model */
    void createPipelineLayout(const PipelineLayoutModel &model);
};