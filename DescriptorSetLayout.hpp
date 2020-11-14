/**
 * @ Author: Pierre Veysseyre
 * @ Description: DescriptorSetLayout
 */

#pragma once

#include "VulkanHandle.hpp"
#include "DescriptorSetLayoutModel.hpp"

namespace kF::Graphics
{
    class DescriptorSetLayout;
};

/** @brief Abstract an DescriptorSetLayout */
class kF::Graphics::DescriptorSetLayout final : public VulkanHandle<DescriptorSetLayoutHandle>
{
public:
    /** @brief Helper that construct a descriptor set layout out of descriptor set layout bindings */
    template<typename ...Bindings>
        requires (... && std::is_same_v<Bindings, DescriptorSetLayoutBinding>)
    [[nodiscard]] static DescriptorSetLayout Make(const DescriptorSetLayoutCreateFlags flags, Bindings &&...bindings) noexcept;


    /** @brief Construct a new DescriptorSetLayout using DescriptorSetLayout model */
    DescriptorSetLayout(const DescriptorSetLayoutModel model) { createDescriptorSetLayout(model); }

    /** @brief Move constructor */
    DescriptorSetLayout(DescriptorSetLayout &&other) noexcept = default;

    /** @brief Destruct the buffer */
    ~DescriptorSetLayout(void) noexcept;

    /** @brief Move assignment */
    DescriptorSetLayout &operator=(DescriptorSetLayout &&other) noexcept = default;

private:
    /** @brief Create an DescriptorSetLayout */
    void createDescriptorSetLayout(const DescriptorSetLayoutModel &model);
};

#include "DescriptorSetLayout.ipp"