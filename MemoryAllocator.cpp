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

}

Graphics::MemoryAllocation Graphics::MemoryAllocator::allocate(const MemoryAllocationModel &model)
{

}

void Graphics::MemoryAllocator::deallocate(const MemoryAllocation allocation)
{

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
        preferredLargeHeapBlockSize: 0u,
        pAllocationCallbacks: nullptr,
        pDeviceMemoryCallbacks: nullptr,
        frameInUseCount: parent().getFramebufferHandler().frameCount(),
        pHeapSizeLimit: nullptr,
        pVulkanFunctions: nullptr,
        pRecordSettings: nullptr,
        instance: parent().getInstance(),
        vulkanApiVersion: VK_API_VERSION_1_1
    };

    if (const auto res = ::vmaCreateAllocator(&allocatorCreateInfo, &handle()); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::MemoryAllocator::createMemoryAllocator: Couldn't create allocator '" + ErrorMessage(res) + '\'');
}