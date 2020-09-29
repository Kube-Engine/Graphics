/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Device buffer
 */

#pragma once

#include "Vulkan.hpp"
#include "RendererObject.hpp"
#include "BufferModel.hpp"

namespace kF
{
    class Buffer;

    using DeviceBuffer = VkBuffer;
    using DeviceMemory = VkDeviceMemory;
    using MemoryPropertyFlags = VkMemoryPropertyFlags;
}

class kF::Buffer : public RendererObject
{
public:
    Buffer(Renderer &renderer, const BufferModel &model);
    Buffer(Buffer &&other) noexcept : RendererObject(other.parent()) { swap(other); }
    ~Buffer(void);

    Buffer &operator=(Buffer &&other) noexcept { swap(other); return *this; }

    void swap(Buffer &other) noexcept;

    [[nodiscard]] DeviceBuffer getDeviceBuffer(void) const noexcept { return _buffer; }
    [[nodiscard]] DeviceMemory getDeviceMemory(void) const noexcept { return _memory; }

private:
    DeviceBuffer _buffer;
    DeviceMemory _memory;

    void createDeviceBuffer(const BufferModel &model);
    void createDeviceMemory(const BufferModel &model);
    void fillBuffer(const BufferModel &model);

    [[nodiscard]] std::uint32_t findMemoryType(const std::uint32_t type, const MemoryPropertyFlags flags);
};