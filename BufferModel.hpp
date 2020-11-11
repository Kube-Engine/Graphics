/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Buffer model
 */

#pragma once

#include "Vulkan.hpp"

namespace kF::Graphics
{
    struct BufferModel;
}

/** @brief A buffer model describes a buffer that should be copied to GPU memory */
struct kF::Graphics::BufferModel : public VkBufferCreateInfo
{
    /** @brief Helper used to create a staging buffer model */
    [[nodiscard]] static inline auto MakeStaging(const BufferSize size) noexcept
        { return BufferModel(0u, size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_SHARING_MODE_EXCLUSIVE); }


    /** @brief Helper used to create a local (GPU only) vertex buffer model */
    [[nodiscard]] static inline auto MakeVertexLocal(const BufferSize size) noexcept
        { return BufferModel(0u, size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_SHARING_MODE_EXCLUSIVE); }

    /** @brief Helper used to create a shared (CPU & GPU) vertex buffer model */
    [[nodiscard]] static inline auto MakeVertexShared(const BufferSize size) noexcept
        { return BufferModel(0u, size, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_SHARING_MODE_EXCLUSIVE); }


    /** @brief Helper used to create a local (GPU only) index buffer model */
    [[nodiscard]] static inline auto MakeIndexLocal(const BufferSize size) noexcept
        { return BufferModel(0u, size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_SHARING_MODE_EXCLUSIVE); }

    /** @brief Helper used to create a shared (CPU & GPU) index buffer model */
    [[nodiscard]] static inline auto MakeIndexShared(const BufferSize size) noexcept
        { return BufferModel(0u, size, VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_SHARING_MODE_EXCLUSIVE); }


    /** @brief Initialize constructor */
    BufferModel(const BufferCreateFlags flags_, const BufferSize size_, const BufferUsageFlags usage_, const SharingMode sharingMode_)
        noexcept
        : VkBufferCreateInfo(
            sType: VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
            pNext: nullptr,
            flags: flags_,
            size: size_,
            usage: usage_,
            sharingMode: sharingMode_,
            queueFamilyIndexCount: 0,
            pQueueFamilyIndices: nullptr,
        ) {}

    /** @brief POD semantics */
    BufferModel(const BufferModel &other) noexcept = default;
    BufferModel(BufferModel &&other) noexcept = default;
    BufferModel &operator=(const BufferModel &other) noexcept = default;
    BufferModel &operator=(BufferModel &&other) noexcept = default;
};