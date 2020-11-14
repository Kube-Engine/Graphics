/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: MemoryAllocator
 */

#pragma once

#include <vector>

#include "VulkanHandle.hpp"
#include "MemoryAllocationModel.hpp"

namespace kF::Graphics
{
    class MemoryAllocator;
}

class kF::Graphics::MemoryAllocator : public CachedVulkanHandle<VmaAllocator>
{
public:
    /** @brief Construct a new memory allocator using VMA */
    MemoryAllocator(void) { createMemoryAllocator(); }

    /** @brief Move constructor */
    MemoryAllocator(MemoryAllocator &&other) noexcept = default;

    /** @brief Destruct the buffer */
    ~MemoryAllocator(void) noexcept;

    /** @brief Move assignment */
    MemoryAllocator &operator=(MemoryAllocator &&other) noexcept = default;


    /** @brief Allocate memory */
    [[nodiscard]] MemoryAllocationHandle allocate(const MemoryAllocationModel &model);

    /** @brief Allocate a list of memory */
    void allocate(const MemoryAllocationModel * const modelFrom, const MemoryAllocationModel * const modelTo,
            MemoryAllocationHandle * const allocationFrom, MemoryAllocationHandle * const allocationTo);

    /** @brief Deallocate memory */
    void deallocate(const MemoryAllocationHandle allocation);

    /** @brief Deallocate a list of memory */
    void deallocate(const MemoryAllocationHandle * const allocationFrom, const MemoryAllocationHandle * const allocationTo);

private:
    /** @brief Create a memory allocator */
    void createMemoryAllocator(void);
};