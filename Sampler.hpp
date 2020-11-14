/**
 * @ Author: Pierre Veysseyre
 * @ Description: Sampler
 */

#pragma once

#include "VulkanHandle.hpp"
#include "SamplerModel.hpp"

namespace kF::Graphics
{
    class Sampler;
};

class kF::Graphics::Sampler final : public VulkanHandle<SamplerHandle>
{
public:
    /** @brief Construct the sampler using its model */
    Sampler(const SamplerModel &model) { createSampler(model); }

    /** @brief Move constructor */
    Sampler(Sampler &&other) noexcept = default;

    /** @brief Destruct the buffer */
    ~Sampler(void) noexcept;

    /** @brief Move assignment */
    Sampler &operator=(Sampler &&other) noexcept = default;

private:
    /** @brief Create a sampler  */
    void createSampler(const SamplerModel &model);
};