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
    /** @brief Make a descriptor set write model for a buffer descriptor */
    [[nodiscard]] static DescriptorSetWriteModel MakeBufferWriteModel(
            DescriptorSet &dstDescriptorSet, const std::uint32_t dstBinding, const DescriptorType descriptorType,
            const DescriptorBufferInfo * const bufferInfoBegin, const DescriptorBufferInfo * const bufferInfoEnd) noexcept;

    /** @brief Make a descriptor set write model for a image descriptor */
    [[nodiscard]] static DescriptorSetWriteModel MakeImageWriteModel(
            DescriptorSet &dstDescriptorSet, const std::uint32_t dstBinding, const DescriptorType descriptorType,
            const DescriptorImageInfo * const imageInfoBegin, const DescriptorImageInfo * const imageInfoEnd) noexcept;

    /** @brief Make a descriptor set write model for a texel descriptor */
    [[nodiscard]] static DescriptorSetWriteModel MakeImageWriteModel(
            DescriptorSet &dstDescriptorSet, const std::uint32_t dstBinding, const DescriptorType descriptorType,
            const BufferViewHandle * const bufferViewBegin, const BufferViewHandle * const bufferViewEnd) noexcept;


    /** @brief Initialize constructor */
    DescriptorSetWriteModel(
            const DescriptorSet &dstDescriptorSet, const std::uint32_t dstBinding_, const std::uint32_t dstArrayElement_,
            const std::uint32_t descriptorCount_, const DescriptorType descriptorType_,
            const DescriptorImageInfo *pImageInfo_, const DescriptorBufferInfo *pBufferInfo_, const BufferViewHandle *pTexelBufferView_)
        noexcept
        : VkWriteDescriptorSet {
            sType: VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
            pNext: nullptr,
            dstSet: dstDescriptorSet,
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

#include "DescriptorSetWriteModel.ipp"
