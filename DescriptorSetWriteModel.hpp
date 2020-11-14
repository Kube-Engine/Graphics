/**
 * @ Author: Pierre Veysseyre
 * @ Description: DescriptorSetWrite
 */

#include "VulkanHandle.hpp"

namespace kF::Graphics
{
    struct DescriptorSetWriteModel;
};


/** @brief Describe how to create descriptor update write command */
struct kF::Graphics::DescriptorSetWriteModel : public VkWriteDescriptorSet
{
    /** @brief Initialize constructor */
    DescriptorSetWriteModel(
            const DescriptorSetHandle dstSet_, const std::uint32_t dstBinding_, const std::uint32_t dstArrayElement_,
            const std::uint32_t descriptorCount_, const DescriptorType descriptorType_,
            const DescriptorImageInfo *pImageInfo_, const DescriptorBufferInfo *pBufferInfo_, const BufferViewHandle *pTexelBufferView_)
        noexcept
        : VkWriteDescriptorSet {
            sType: VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
            pNext: nullptr,
            dstSet: dstSet_,
            dstBinding: dstBinding_,
            dstArrayElement: dstArrayElement_,
            descriptorCount: descriptorCount_,
            descriptorType: static_cast<VkDescriptorType>(descriptorType_),
            pImageInfo: pImageInfo_,
            pBufferInfo: pBufferInfo_,
            pTexelBufferView: pTexelBufferView_
        } {}

    /** @brief POD semantics */
    DescriptorSetWriteModel(const DescriptorSetWriteModel &other) noexcept = default;
    DescriptorSetWriteModel(DescriptorSetWriteModel &&other) noexcept = default;
    DescriptorSetWriteModel &operator=(const DescriptorSetWriteModel &other) noexcept = default;
    DescriptorSetWriteModel &operator=(DescriptorSetWriteModel &&other) noexcept = default;

};
