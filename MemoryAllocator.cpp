/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: MemoryAllocator
 */

#define VMA_IMPLEMENTATION
#include <vk_mem_alloc.h>

#include <Kube/Core/StringLiteral.hpp>

#include "Renderer.hpp"
#include "MemoryAllocator.hpp"

using namespace kF;
using namespace kF::Literal;

Graphics::MemoryAllocator::~MemoryAllocator(void) noexcept
{
    ::vmaDestroyAllocator(handle());
}

void Graphics::MemoryAllocator::allocate(const MemoryAllocationModel * const modelFrom, const MemoryAllocationModel * const modelTo,
        MemoryAllocationHandle * const allocationFrom, MemoryAllocationHandle * const allocationTo)
{
    kFAssert(std::distance(modelFrom, modelTo) == std::distance(allocationFrom, allocationTo),
        throw std::logic_error("Graphics::MemoryAllocator::allocate: Mismatching model count and allocation count"));

    auto allocationIt = allocationFrom;
    for (auto modelIt = modelFrom; modelIt != modelTo; ++modelIt, ++allocationIt) {
        VmaAllocationCreateInfo allocationCreateInfo = {
            flags: VmaAllocationCreateFlags(),
            usage: static_cast<VmaMemoryUsage>(modelIt->memoryUsage()), // easy way to specify memory requirements
            requiredFlags: 0u,
            preferredFlags: 0u,
            memoryTypeBits: 0u, // no restriction for memory types
            pool: nullptr,
            pUserData: nullptr
        };
        if (modelIt->bindType() == MemoryAllocationModel::BindType::Buffer) {
            auto res = ::vmaAllocateMemoryForBuffer(
                handle(),
                modelIt->buffer(),
                &allocationCreateInfo,
                allocationIt,
                nullptr
            );
            if (res != VK_SUCCESS)
                throw std::runtime_error(std::string("Graphics::MemoryAllocator::allocate: Couldn't allocate memory for buffer '") + ErrorMessage(res) + '\'');
            res = ::vmaBindBufferMemory(handle(), *allocationIt, modelIt->buffer());
            if (res != VK_SUCCESS)
                throw std::runtime_error(std::string("Graphics::MemoryAllocator::allocate: Couldn't bind memory to buffer '") + ErrorMessage(res) + '\'');
        } else {
            auto res = ::vmaAllocateMemoryForImage(
                handle(),
                modelIt->image(),
                &allocationCreateInfo,
                allocationIt,
                nullptr
            );
            if (res != VK_SUCCESS)
                throw std::runtime_error(std::string("Graphics::MemoryAllocator::allocate: Couldn't allocate memory for image '") + ErrorMessage(res) + '\'');
            res = ::vmaBindImageMemory(handle(), *allocationIt, modelIt->image());
            if (res != VK_SUCCESS)
                throw std::runtime_error(std::string("Graphics::MemoryAllocator::allocate: Couldn't bind memory to image '") + ErrorMessage(res) + '\'');
        }
    }
}

void Graphics::MemoryAllocator::deallocate(const MemoryAllocationHandle * const allocationFrom, const MemoryAllocationHandle * const allocationTo)
{
    for (auto allocationIt = allocationFrom; allocationIt != allocationTo; ++allocationIt) {
        ::vmaFreeMemory(handle(), *allocationIt);
    }
}

void Graphics::MemoryAllocator::createMemoryAllocator(void)
{
    VmaAllocatorCreateInfo allocatorCreateInfo {
        flags: VmaAllocatorCreateFlags(),
        physicalDevice: parent().physicalDevice(),
        device: parent().logicalDevice(),
        preferredLargeHeapBlockSize: 0u, // 0 for default VkDeviceMemory block size = 256MB
        pAllocationCallbacks: nullptr,
        pDeviceMemoryCallbacks: nullptr,
        frameInUseCount: static_cast<std::uint32_t>(parent().cachedFrameCount()),
        pHeapSizeLimit: nullptr, // NULL for no limit on maximum number of bytes that can be allocated on a particular Vulkan heap
        pVulkanFunctions: nullptr,
        pRecordSettings: nullptr,
        instance: parent().instance(),
        vulkanApiVersion: VK_API_VERSION_1_1
    };

    if (const auto res = ::vmaCreateAllocator(&allocatorCreateInfo, &handle()); res != VK_SUCCESS)
        throw std::runtime_error(std::string("Graphics::MemoryAllocator::createMemoryAllocator: Couldn't create allocator '") + ErrorMessage(res) + '\'');
}