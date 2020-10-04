/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Device buffer
 */

#pragma once

#include "Vulkan.hpp"
#include "RendererObject.hpp"
#include "BufferModel.hpp"

namespace kF::Graphics
{
    class Buffer;

    /** @brief Vulkan buffer */
    using DeviceBuffer = VkBuffer;

    /** @brief A list of device buffers */
    using DeviceBuffers = std::vector<DeviceBuffer>;

    /** @brief Vulkan memory */
    using DeviceMemory = VkDeviceMemory;

    /** @brief Vulkan memory properties */
    using MemoryPropertyFlags = VkMemoryPropertyFlags;
}

/** @brief GPU Memory buffer abstraction */
class kF::Graphics::Buffer : public RendererObject
{
public:
    /** @brief Construct a nw buffer using a buffer model */
    Buffer(Renderer &renderer, const BufferModel &model);

    /** @brief Move constructor */
    Buffer(Buffer &&other) noexcept : RendererObject(other.parent()) { swap(other); }

    /** @brief Destruct the buffer */
    ~Buffer(void) noexcept;

    /** @brief Move assignment */
    Buffer &operator=(Buffer &&other) noexcept { swap(other); return *this; }

    /** @brief Swap two instances */
    void swap(Buffer &other) noexcept;

    /** @brief Get device buffer */
    [[nodiscard]] DeviceBuffer getDeviceBuffer(void) const noexcept { return _buffer; }

    /** @brief Get device memory */
    [[nodiscard]] DeviceMemory getDeviceMemory(void) const noexcept { return _memory; }

private:
    DeviceBuffer _buffer;
    DeviceMemory _memory;

    /** @brief Create the device buffer */
    void createDeviceBuffer(const BufferModel &model);

    /** @brief Create the device memory */
    void createDeviceMemory(const BufferModel &model);

    /** @brief Fill the buffer using a model */
    void fillBuffer(const BufferModel &model) noexcept;

    /** @brief Helper to find a memory type index */
    [[nodiscard]] std::uint32_t findMemoryType(const std::uint32_t type, const MemoryPropertyFlags flags) const;
};