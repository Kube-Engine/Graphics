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

/** @brief Describe how to create a buffer */
struct kF::Graphics::BufferModel : public VkBufferCreateInfo
{
    /** @brief Helper used to create a staging buffer model */
    [[nodiscard]] static BufferModel MakeStaging(const BufferSize size) noexcept;

    /** @brief Helper used to create a local (GPU only) vertex buffer model */
    [[nodiscard]] static BufferModel MakeVertexLocal(const BufferSize size) noexcept;

    /** @brief Helper used to create a shared (CPU & GPU) vertex buffer model */
    [[nodiscard]] static BufferModel MakeVertexShared(const BufferSize size) noexcept;

    /** @brief Helper used to create a local (GPU only) index buffer model */
    [[nodiscard]] static BufferModel MakeIndexLocal(const BufferSize size) noexcept;

    /** @brief Helper used to create a shared (CPU & GPU) index buffer model */
    [[nodiscard]] static BufferModel MakeIndexShared(const BufferSize size) noexcept;


    /** @brief Initialize constructor */
    BufferModel(const BufferCreateFlags flags_, const BufferSize size_, const BufferUsageFlags usage_, const SharingMode sharingMode_,
            const std::uint32_t * const queueFamilyIndexBegin, const std::uint32_t * const queueFamilyIndexEnd)
        noexcept
        : VkBufferCreateInfo {
            sType: VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
            pNext: nullptr,
            flags: ToFlags(flags_),
            size: size_,
            usage: ToFlags(usage_),
            sharingMode: static_cast<VkSharingMode>(sharingMode_),
            queueFamilyIndexCount: static_cast<std::uint32_t>(std::distance(queueFamilyIndexBegin, queueFamilyIndexEnd)),
            pQueueFamilyIndices: queueFamilyIndexBegin
        } {}

    /** @brief POD semantics */
    BufferModel(const BufferModel &other) noexcept = default;
    BufferModel(BufferModel &&other) noexcept = default;
    BufferModel &operator=(const BufferModel &other) noexcept = default;
    BufferModel &operator=(BufferModel &&other) noexcept = default;
};

#include "BufferModel.ipp"