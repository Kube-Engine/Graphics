/**
 * @ Author: Pierre Veysseyre
 * @ Description: DescriptorPool
 */

#pragma once

#include "VulkanHandle.hpp"
#include "DescriptorPoolModel.hpp"
#include "DescriptorSetLayout.hpp"

namespace kF::Graphics
{
    class DescriptorPool;
};

/** @brief Abstract an DescriptorPool */
class kF::Graphics::DescriptorPool final : public VulkanHandle<VkDescriptorPool>
{
public:
    /** @brief Construct a new DescriptorPool using DescriptorPool model */
    DescriptorPool(Renderer &renderer, const DescriptorPoolModel &model) : VulkanHandle<DescriptorPoolHandle>(renderer)
        { createDescriptorPool(model); }

    /** @brief Move constructor */
    DescriptorPool(DescriptorPool &&other) noexcept = default;

    /** @brief Destruct the buffer */
    ~DescriptorPool(void) noexcept;

    /** @brief Move assignment */
    DescriptorPool &operator=(DescriptorPool &&other) noexcept = default;

    /** @brief Allocate descriptor sets from descriptor set layouts */
    void allocateDescriptorSets(const DescriptorSetLayout * const layoutBengin, const DescriptorSetLayout * const layoutEnd,
            const DescriptorSet * descriptorSetBegin, const DescriptorSet * descriptorSetEnd);

private:
    /** @brief Create an DescriptorPool */
    void createDescriptorPool(const DescriptorPoolModel &model);
};

#include "DescriptorPool.ipp"
