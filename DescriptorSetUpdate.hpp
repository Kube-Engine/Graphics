/**
 * @ Author: Pierre Veysseyre
 * @ Description: DescriptorSetWrite
 */

#include "DescriptorSetWriteModel.hpp"
#include "DescriptorSetCopyModel.hpp"

namespace kF::Graphics
{
    struct DescriptorSetUpdate;
};

struct kF::Graphics::DescriptorSetUpdate
{
    /** @brief Write update of a descriptor set */
    static void UpdateWrite(
            const DescriptorSetWriteModel * const writeModelBegin, const DescriptorSetWriteModel * const writeModelEnd) noexcept;

    /** @brief Copy update of a descriptor set */
    static void UpdateCopy(
            const DescriptorSetCopyModel * const copyModelBegin, const DescriptorSetCopyModel * const copyModelEnd) noexcept;

    /** @brief Write & copy update of a descriptor set */
    static void UpdateWriteAndCopy(
            const DescriptorSetWriteModel * const writeModelBegin, const DescriptorSetWriteModel * const writeModelEnd,
            const DescriptorSetCopyModel * const copyModelBegin, const DescriptorSetCopyModel * const copyModelEnd) noexcept;
};
