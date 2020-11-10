/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: MemoryAllocator
 */

#pragma once

#include <vector>

#include "VulkanHandler.hpp"
#include "MemoryAllocationModel.hpp"

namespace kF::Graphics
{
    class MemoryAllocator;

    /** @brief Device memory allocation */
    using MemoryAllocation = VmaAllocation;
}

class kF::Graphics::MemoryAllocator : public VulkanHandler<VmaAllocator>
{
public:
    /** @brief Construct a new memory allocator using VMA */
    MemoryAllocator(Renderer &renderer) : VulkanHandler<VmaAllocator>(renderer)
        { createMemoryAllocator(); }

    /** @brief Move constructor */
    MemoryAllocator(MemoryAllocator &&other) noexcept = default;

    /** @brief Destruct the buffer */
    ~MemoryAllocator(void) noexcept;

    /** @brief Move assignment */
    MemoryAllocator &operator=(MemoryAllocator &&other) noexcept = default;


    /** @brief Allocate memory */
    [[nodiscard]] MemoryAllocation allocate(const MemoryAllocationModel &model);

    /** @brief Allocate a list of memory */
    [[nodiscard]] void allocate(const MemoryAllocationModel * const modelFrom, const MemoryAllocationModel * const modelTo,
            MemoryAllocation * const allocationFrom, MemoryAllocation * const allocationTo);

    /** @brief Deallocate memory */
    void deallocate(const MemoryAllocation allocation);

    /** @brief Deallocate a list of memory */
    void deallocate(const MemoryAllocation * const allocationFrom, const MemoryAllocation * const allocationTo);

private:
    /** @brief Create a memory allocator */
    void createMemoryAllocator(void);
};