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
class kF::Graphics::DescriptorPool final : public CachedVulkanHandle<VkDescriptorPool>
{
public:
    /** @brief Construct a new DescriptorPool using DescriptorPool model */
    DescriptorPool(const DescriptorPoolModel &model) { createDescriptorPool(model); }

    /** @brief Move constructor */
    DescriptorPool(DescriptorPool &&other) noexcept = default;

    /** @brief Destruct the buffer */
    ~DescriptorPool(void) noexcept;

    /** @brief Move assignment */
    DescriptorPool &operator=(DescriptorPool &&other) noexcept = default;


    /** @brief Allocate descriptor sets from descriptor set layouts */
    void allocateDescriptorSets(
            const DescriptorSetLayoutHandle * const layoutBengin, const DescriptorSetLayoutHandle * const layoutEnd,
            DescriptorSetHandle * const descriptorSetBegin, DescriptorSetHandle * const descriptorSetEnd);

private:
    /** @brief Create an DescriptorPool */
    void createDescriptorPool(const DescriptorPoolModel &model);
};
