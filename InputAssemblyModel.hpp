/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: InputAssemblyModel
 */

#pragma once

#include "Vulkan.hpp"

namespace kF::Graphics
{
    struct InputAssemblyModel;
};

/** @brief Describe how to create a sampler */
struct kF::Graphics::InputAssemblyModel : public VkPipelineInputAssemblyStateCreateInfo
{
    /** @brief Initialize constructor */
    InputAssemblyModel(const InputAssemblyCreateFlags flags_, const PrimitiveTopology topology_, const bool primitiveRestartEnable_)
        noexcept
        : VkPipelineInputAssemblyStateCreateInfo {
            sType: VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
            pNext: nullptr,
            flags: ToFlags(flags_),
            topology: topology_,
            primitiveRestartEnable: primitiveRestartEnable_
        } {}

    /** @brief POD semantics */
    InputAssemblyModel(const InputAssemblyModel &other) noexcept = default;
    InputAssemblyModel(InputAssemblyModel &&other) noexcept = default;
    InputAssemblyModel &operator=(const InputAssemblyModel &other) noexcept = default;
    InputAssemblyModel &operator=(InputAssemblyModel &&other) noexcept = default;
};
