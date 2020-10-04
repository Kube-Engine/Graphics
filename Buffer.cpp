/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Buffer
 */

#include <cstring>

#include "Renderer.hpp"

using namespace kF;
using namespace kF::Literal;

Graphics::Buffer::Buffer(Renderer &renderer, const BufferModel &model) : RendererObject(renderer)
{
    createDeviceBuffer(model);
    createDeviceMemory(model);
    fillBuffer(model);
}

Graphics::Buffer::~Buffer(void) noexcept
{
    ::vkDestroyBuffer(parent().getLogicalDevice(), _buffer, nullptr);
    ::vkFreeMemory(parent().getLogicalDevice(), _memory, nullptr);
}

void Graphics::Buffer::swap(Buffer &other) noexcept
{
    std::swap(_buffer, other._buffer);
    std::swap(_memory, other._memory);
}

void Graphics::Buffer::createDeviceBuffer(const BufferModel &model)
{
    VkBufferCreateInfo bufferInfo {
        sType: VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        pNext: nullptr,
        flags: 0,
        size: model.size,
        usage: VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
        sharingMode: VK_SHARING_MODE_EXCLUSIVE,
        queueFamilyIndexCount: 0,
        pQueueFamilyIndices: nullptr,
    };

    if (auto res = ::vkCreateBuffer(parent().getLogicalDevice(), &bufferInfo, nullptr, &_buffer); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::Buffer::createDeviceBuffer: Couldn't create buffer '"_str + ErrorMessage(res) + '\'');
}

void Graphics::Buffer::createDeviceMemory(const BufferModel &model)
{
    VkMemoryRequirements memoryRequirements;
    ::vkGetBufferMemoryRequirements(parent().getLogicalDevice(), _buffer, &memoryRequirements);
    VkMemoryAllocateInfo memoryAllocateInfo {
        sType: VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        pNext: nullptr,
        allocationSize: memoryRequirements.size,
        memoryTypeIndex: findMemoryType(
            memoryRequirements.memoryTypeBits,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
        )
    };

    if (auto res = ::vkAllocateMemory(parent().getLogicalDevice(), &memoryAllocateInfo, nullptr, &_memory))
        throw std::runtime_error("Graphics::Buffer::createDeviceMemory: Couldn't allocate device memory '"_str + ErrorMessage(res) + '\'');
    ::vkBindBufferMemory(parent().getLogicalDevice(), _buffer, _memory, 0);
}

void Graphics::Buffer::fillBuffer(const BufferModel &model) noexcept
{
    void *data = nullptr;

    ::vkMapMemory(parent().getLogicalDevice(), _memory, 0, model.size, 0, &data);
    std::memcpy(data, model.data, model.size);
    ::vkUnmapMemory(parent().getLogicalDevice(), _memory);
}

std::uint32_t Graphics::Buffer::findMemoryType(const std::uint32_t type, const MemoryPropertyFlags flags) const
{
    VkPhysicalDeviceMemoryProperties properties;

    ::vkGetPhysicalDeviceMemoryProperties(parent().getPhysicalDevice(), &properties);
    for (auto i = 0u; i < properties.memoryTypeCount; ++i) {
        if (type & (1 << i) && (properties.memoryTypes[i].propertyFlags & flags))
            return i;
    }
    throw std::runtime_error("Graphics::Buffer::findMemoryType: Couldn't find memory type");
}
