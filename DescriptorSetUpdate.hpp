/**
 * @ Author: Pierre Veysseyre
 * @ Description: DescriptorSetWrite
 */

#include "Renderer.hpp"
#include "DescriptorSetWriteModel.hpp"
// #include "DescriptorSetCopyModel.hpp"

namespace kF::Graphics
{
    struct DescriptorSetUpdate;
};

struct kF::Graphics::DescriptorSetUpdate
{
    /** @brief Write update of a descriptor set */
    static void UpdateWrite(Renderer &renderer,
            const DescriptorSetWriteModel * const writeModelBegin, const DescriptorSetWriteModel * const writeModelEnd) noexcept {
        vkUpdateDescriptorSets(
            renderer.logicalDevice(),
            static_cast<std::uint32_t>(std::distance(writeModelBegin, writeModelEnd)),
            writeModelBegin,
            0,
            nullptr
        );
    }

    // /** @brief Copy update of a descriptor set */
    // static void UpdateCopy(Renderer &renderer,
    //         const DescriptorSetCopyModel * const copyModelBegin, const DescriptorSetCopyModel * const copyModelEnd) noexcept {
    //     vkUpdateDescriptorSets(
    //         renderer.logicalDevice(),
    //         0,
    //         nullptr,
    //         static_cast<std::uint32_t>(std::distance(copyModelBegin, copyModelEnd)), copyModelBegin
    //     );
    // }

    // /** @brief Write & copy update of a descriptor set */
    // static void UpdateWriteAndCopy(Renderer &renderer,
    //         const DescriptorSetWriteModel * const writeModelBegin, const DescriptorSetWriteModel * const writeModelEnd,
    //         const DescriptorSetCopyModel * const copyModelBegin, const DescriptorSetCopyModel * const copyModelEnd) noexcept {
    //     vkUpdateDescriptorSets(
    //         renderer.logicalDevice(),
    //         static_cast<std::uint32_t>(std::distance(writeModelBegin, writeModelEnd)),
    //         writeModelBegin,
    //         static_cast<std::uint32_t>(std::distance(copyModelBegin, copyModelEnd)),
    //         copyModelBegin
    //     );
    // }
};

#include "DescriptorSetUpdate.ipp"