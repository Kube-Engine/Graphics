/**
 * @ Author: Pierre Veysseyre
 * @ Description: DescriptorSetCopy
 */

#include "VulkanHandle.hpp"

namespace kF::Graphics
{
    struct DescriptorSetCopyModel;
};


/** @brief Describe how to create descriptor update copy command */
struct kF::Graphics::DescriptorSetCopyModel : public VkWriteDescriptorSet
{
    /** @brief Make a descriptor set copy model */
    [[nodiscard]] static DescriptorSetCopyModel MakeCopyModel(
            const DescriptorSet &dstDescriptorSet, const std::uint32_t dstBinding_, const std::uint32_t dstArrayElement_,
            const DescriptorSet &srcDescriptorSet, const std::uint32_t srcBinding_, const std::uint32_t srcArrayElement_,
            const std::uint32_t descriptorCount_) noexcept {
        return DescriptorSetCopyModel(
            dstDescriptorSet,
            dstBinding_,
            dstArrayElement_,
            srcDescriptorSet,
            srcBinding_,
            srcArrayElement_,
            descriptorCount_
        );
    }

    /** @brief Initialize constructor */
    DescriptorSetCopyModel(
            const DescriptorSet &dstDescriptorSet, const std::uint32_t dstBinding_, const std::uint32_t dstArrayElement_,
            const DescriptorSet &srcDescriptorSet, const std::uint32_t srcBinding_, const std::uint32_t srcArrayElement_,
            const std::uint32_t descriptorCount_)
        noexcept
        : VkWriteDescriptorSet {
            sType: VK_STRUCTURE_TYPE_COPY_DESCRIPTOR_SET,
            pNext: nullptr,
            srcSet: dstDescriptorSet,
            srcBinding: srcBinding_,
            srcArrayElement: srcArrayElement_,
            dstSet: srcDescriptorSet,
            dstBinding: dstBinding_,
            dstArrayElement: dstArrayElement_,
            descriptorCount: descriptorCount_
        } {}

    /** @brief POD semantics */
    DescriptorSetCopyModel(const DescriptorSetCopyModel &other) noexcept = default;
    DescriptorSetCopyModel(DescriptorSetCopyModel &&other) noexcept = default;
    DescriptorSetCopyModel &operator=(const DescriptorSetCopyModel &other) noexcept = default;
    DescriptorSetCopyModel &operator=(DescriptorSetCopyModel &&other) noexcept = default;

};

#include "DescriptorSetCopyModel.ipp"
