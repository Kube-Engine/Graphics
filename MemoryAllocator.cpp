/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: MemoryAllocator
 */

#define VMA_IMPLEMENTATION
#include <vk_mem_alloc.h>

#include "Renderer.hpp"
#include "MemoryAllocator.hpp" // delete me later

using namespace kF;

Graphics::MemoryAllocator::MemoryAllocator(Renderer &renderer) : VulkanHandler<VmaAllocator>(renderer)
{
    createMemoryAllocator();
}

Graphics::MemoryAllocator::~MemoryAllocator(void) noexcept
{
    ::vmaDestroyAllocator(handle());
}

Graphics::MemoryAllocation Graphics::MemoryAllocator::allocate(const MemoryAllocationModel &model)
{    
    VmaAllocation newAllocation;
    VmaAllocationCreateInfo allocationCreateInfo = {
        .flags = VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT, // ? look for best combination
        .usage = static_cast<VmaMemoryUsage>(model.memoryUsage()), // easy way to specify memory requirements
        .requiredFlags = 0u,
        .preferredFlags = 0u,
        .memoryTypeBits = 0u, // no restriction for memory types
        .pool = nullptr,
        .pUserData = nullptr
    };
    if (model.memoryType() == MemoryType::Buffer) {
        auto res = ::vmaAllocateMemoryForBuffer(
            handle(), 
            model.buffer(), 
            &allocationCreateInfo, 
            &newAllocation, 
            nullptr
        );
        if (res != VK_SUCCESS)
            throw std::runtime_error(std::string("Graphics::MemoryAllocator::allocate: Couldn't allocate memory for buffer '") + ErrorMessage(res) + '\'');
        res = ::vmaBindBufferMemory(handle(), newAllocation, model.buffer());
        if (res != VK_SUCCESS)
            throw std::runtime_error(std::string("Graphics::MemoryAllocator::allocate: Couldn't bind memory to buffer '") + ErrorMessage(res) + '\'');
    } else {
        auto res = ::vmaAllocateMemoryForImage(
            handle(), 
            model.image(), 
            &allocationCreateInfo, 
            &newAllocation, 
            nullptr
        );
        if (res != VK_SUCCESS)
            throw std::runtime_error(std::string("Graphics::MemoryAllocator::allocate: Couldn't allocate memory for image '") + ErrorMessage(res) + '\'');
        res = ::vmaBindImageMemory(handle(), newAllocation, model.image());
        if (res != VK_SUCCESS)
            throw std::runtime_error(std::string("Graphics::MemoryAllocator::allocate: Couldn't bind memory to image '") + ErrorMessage(res) + '\'');
    }
    return newAllocation;
}

void Graphics::MemoryAllocator::deallocate(const MemoryAllocation allocation)
{
    ::vmaFreeMemory(handle(), allocation);
}

Graphics::MemoryAllocation Graphics::MemoryAllocator::allocate(const std::vector<MemoryAllocationModel> &models)
{
    
}

void Graphics::MemoryAllocator::deallocate(const std::vector<MemoryAllocation> &allocations)
{

}

void Graphics::MemoryAllocator::createMemoryAllocator(void)
{
    VmaAllocatorCreateInfo allocatorCreateInfo {
        flags: 0,
        physicalDevice: parent().getPhysicalDevice(),
        device: parent().getLogicalDevice(),
        preferredLargeHeapBlockSize: 0u, // 0 for default VkDeviceMemory block size = 256MB
        pAllocationCallbacks: nullptr,
        pDeviceMemoryCallbacks: nullptr,
        frameInUseCount: parent().getFramebufferHandler().frameCount(),
        pHeapSizeLimit: nullptr, // NULL for no limit on maximum number of bytes that can be allocated on a particular Vulkan heap
        pVulkanFunctions: nullptr,
        pRecordSettings: nullptr,
        instance: parent().getInstance(),
        vulkanApiVersion: VK_API_VERSION_1_1
    };

    if (const auto res = ::vmaCreateAllocator(&allocatorCreateInfo, &handle()); res != VK_SUCCESS)
        throw std::runtime_error(std::string("Graphics::MemoryAllocator::createMemoryAllocator: Couldn't create allocator '") + ErrorMessage(res) + '\'');
}