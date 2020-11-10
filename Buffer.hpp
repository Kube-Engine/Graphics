/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Device buffer
 */

#pragma once

#include "VulkanHandler.hpp"
#include "RendererObject.hpp"
#include "BufferModel.hpp"

namespace kF::Graphics
{
    class Buffer;

    /** @brief Vulkan buffer */
    using BufferHandle = VkBuffer;

    /** @brief A list of device buffers */
    using BufferHandles = std::vector<BufferHandle>;

    /** @brief Vulkan buffer properties */
    using CommandBufferUsageFlags = VkCommandBufferUsageFlags;
}

/** @brief GPU Memory buffer abstraction */
class kF::Graphics::Buffer : public VulkanHandler<BufferHandle>
{
public:
    /** @brief Construct a nw buffer using a buffer model */
    Buffer(Renderer &renderer, const BufferModel &model);

    /** @brief Move constructor */
    Buffer(Buffer &&other) noexcept : VulkanHandler<BufferHandle>(other.parent()) { swap(other); }

    /** @brief Destruct the buffer */
    ~Buffer(void) noexcept;

    /** @brief Move assignment */
    Buffer &operator=(Buffer &&other) noexcept { swap(other); return *this; }

    /** @brief Swap two instances */
    void swap(Buffer &other) noexcept;

    /** @brief Get device memory */
    [[nodiscard]] DeviceMemory getDeviceMemory(void) const noexcept { return _memory; }

private:
    DeviceMemory _memory;

    /** @brief Create the device buffer */
    void createBufferHandle(const BufferModel &model);

    /** @brief Create the device memory */
    void createDeviceMemory(const BufferModel &model);

    /** @brief Fill the buffer using a model */
    void fillMemory(const BufferModel &model) noexcept;

    /** @brief Helper to find a memory type index */
    [[nodiscard]] std::uint32_t findMemoryType(const std::uint32_t type, const MemoryPropertyFlags flags) const;
};