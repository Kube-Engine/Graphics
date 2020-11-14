/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: DescriporSetUpdate
 */

#include "Renderer.hpp"
#include "DescriptorSetUpdate.hpp"

using namespace kF;

void Graphics::DescriptorSetUpdate::UpdateWrite(
        const DescriptorSetWriteModel * const writeModelBegin, const DescriptorSetWriteModel * const writeModelEnd) noexcept
{
    vkUpdateDescriptorSets(
        RendererObject::Parent().logicalDevice(),
        static_cast<std::uint32_t>(std::distance(writeModelBegin, writeModelEnd)),
        writeModelBegin,
        0,
        nullptr
    );
}

/** @brief Copy update of a descriptor set */
void Graphics::DescriptorSetUpdate::UpdateCopy(
        const DescriptorSetCopyModel * const copyModelBegin, const DescriptorSetCopyModel * const copyModelEnd) noexcept
{
    vkUpdateDescriptorSets(
        RendererObject::Parent().logicalDevice(),
        0,
        nullptr,
        static_cast<std::uint32_t>(std::distance(copyModelBegin, copyModelEnd)), copyModelBegin
    );
}

/** @brief Write & copy update of a descriptor set */
void Graphics::DescriptorSetUpdate::UpdateWriteAndCopy(
        const DescriptorSetWriteModel * const writeModelBegin, const DescriptorSetWriteModel * const writeModelEnd,
        const DescriptorSetCopyModel * const copyModelBegin, const DescriptorSetCopyModel * const copyModelEnd) noexcept
{
    vkUpdateDescriptorSets(
        RendererObject::Parent().logicalDevice(),
        static_cast<std::uint32_t>(std::distance(writeModelBegin, writeModelEnd)),
        writeModelBegin,
        static_cast<std::uint32_t>(std::distance(copyModelBegin, copyModelEnd)),
        copyModelBegin
    );
}