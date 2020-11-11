/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: MemoryAllocator
 */

#pragma once

#include <vector>

#include "VulkanHandle.hpp"
#include "MemoryAllocationHandleModel.hpp"

namespace kF::Graphics
{
    class MemoryAllocator;
}

class kF::Graphics::MemoryAllocator : public VulkanHandle<VmaAllocator>
{
public:
    /** @brief Construct a new memory allocator using VMA */
    MemoryAllocator(Renderer &renderer) : VulkanHandle<VmaAllocator>(renderer)
        { createMemoryAllocator(); }

    /** @brief Move constructor */
    MemoryAllocator(MemoryAllocator &&other) noexcept = default;

    /** @brief Destruct the buffer */
    ~MemoryAllocator(void) noexcept;

    /** @brief Move assignment */
    MemoryAllocator &operator=(MemoryAllocator &&other) noexcept = default;


    /** @brief Allocate memory */
    [[nodiscard]] MemoryAllocationHandle allocate(const MemoryAllocationHandleModel &model);

    /** @brief Allocate a list of memory */
    [[nodiscard]] void allocate(const MemoryAllocationHandleModel * const modelFrom, const MemoryAllocationHandleModel * const modelTo,
            MemoryAllocationHandle * const allocationFrom, MemoryAllocationHandle * const allocationTo);

    /** @brief Deallocate memory */
    void deallocate(const MemoryAllocationHandle allocation);

    /** @brief Deallocate a list of memory */
    void deallocate(const MemoryAllocationHandle * const allocationFrom, const MemoryAllocationHandle * const allocationTo);

private:
    /** @brief Create a memory allocator */
    void createMemoryAllocator(void);
};