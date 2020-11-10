/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Buffer
 */

#include <cstring>

#include "Renderer.hpp"

using namespace kF;
using namespace kF::Literal;

Graphics::Buffer::~Buffer(void) noexcept
{
    ::vkDestroyBuffer(parent().logicalDevice(), handle(), nullptr);
    ::vkFreeMemory(parent().logicalDevice(), _memory, nullptr);
}

void Graphics::Buffer::createBufferHandle(const BufferModel &model)
{
    constexpr auto GetUsage = [](const BufferModel::Location location, const BufferModel::Usage usage) -> VkBufferUsageFlags {
        switch (usage) {
        case BufferModel::Usage::Transfer:
            return VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
        case BufferModel::Usage::Vertex:
            return VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | (location == BufferModel::Location::Local ? VK_BUFFER_USAGE_TRANSFER_DST_BIT : 0);
        case BufferModel::Usage::Index:
            return VK_BUFFER_USAGE_INDEX_BUFFER_BIT | (location == BufferModel::Location::Local ? VK_BUFFER_USAGE_TRANSFER_DST_BIT : 0);
        default:
            return VkBufferUsageFlags();
        }
    };

    VkBufferCreateInfo bufferInfo {
        sType: VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        pNext: nullptr,
        flags: 0,
        size: model.size,
        usage: GetUsage(model.location, model.usage),
        sharingMode: VK_SHARING_MODE_EXCLUSIVE,
        queueFamilyIndexCount: 0,
        pQueueFamilyIndices: nullptr,
    };

    if (auto res = ::vkCreateBuffer(parent().logicalDevice(), &bufferInfo, nullptr, &handle()); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::Buffer::createBufferHandle: Couldn't create buffer '"_str + ErrorMessage(res) + '\'');
}

void Graphics::Buffer::createDeviceMemory(const BufferModel &model)
{
    constexpr auto GetMemoryFlags = [](const BufferModel::Location location) -> MemoryPropertyFlags{
        switch (location) {
        case BufferModel::Location::Local:
            return VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
        case BufferModel::Location::Shared:
            return VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
        default:
            return VkBufferUsageFlags();
        }
    };

    VkMemoryRequirements memoryRequirements;
    ::vkGetBufferMemoryRequirements(parent().logicalDevice(), handle(), &memoryRequirements);
    VkMemoryAllocateInfo memoryAllocateInfo {
        sType: VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        pNext: nullptr,
        allocationSize: memoryRequirements.size,
        memoryTypeIndex: findMemoryType(memoryRequirements.memoryTypeBits, GetMemoryFlags(model.location))
    };

    if (auto res = ::vkAllocateMemory(parent().logicalDevice(), &memoryAllocateInfo, nullptr, &_memory))
        throw std::runtime_error("Graphics::Buffer::createDeviceMemory: Couldn't allocate device memory '"_str + ErrorMessage(res) + '\'');
    ::vkBindBufferMemory(parent().logicalDevice(), handle(), _memory, 0);
}

void Graphics::Buffer::fillMemory(const BufferModel &model) noexcept
{
    // If the location is local, we must use a staging buffer to copy the memory using a transfer queue
    if (model.location == BufferModel::Location::Local) {
        // Create another buffer with shared location
        BufferModel stagingModel = model;
        stagingModel.location = BufferModel::Location::Shared;
        Buffer staging(parent(), stagingModel);
        // Copy the shared location to the local buffer
        auto cmd = parent().commandPool().addCommand(CommandModel {
            lifecycle: CommandModel::Lifecycle::OneTimeSubmit,
            data: TransferModel {
                source: staging,
                destination: handle(),
                size: model.size
            }
        });
        // Execute the command
        // ...
        // Wait until its done
        // ...
    // Else, we can directly use shared memory
    } else if (model.location == BufferModel::Location::Shared) {
        void *data = nullptr;
        ::vkMapMemory(parent().logicalDevice(), _memory, 0, model.size, 0, &data);
        std::memcpy(data, model.data, model.size);
        ::vkUnmapMemory(parent().logicalDevice(), _memory);
    }
}

std::uint32_t Graphics::Buffer::findMemoryType(const std::uint32_t type, const MemoryPropertyFlags flags) const
{
    VkPhysicalDeviceMemoryProperties properties;

    ::vkGetPhysicalDeviceMemoryProperties(parent().physicalDevice(), &properties);
    for (auto i = 0u; i < properties.memoryTypeCount; ++i) {
        if (type & (1 << i) && (properties.memoryTypes[i].propertyFlags & flags))
            return i;
    }
    throw std::runtime_error("Graphics::Buffer::findMemoryType: Couldn't find memory type");
}
