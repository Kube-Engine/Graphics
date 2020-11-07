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
    MemoryAllocator(Renderer &renderer);

    /** @brief Move constructor */
    MemoryAllocator(MemoryAllocator &&other) noexcept = default;

    /** @brief Destruct the buffer */
    ~MemoryAllocator(void) noexcept;

    /** @brief Move assignment */
    MemoryAllocator &operator=(MemoryAllocator &&other) noexcept = default;


    /** @brief Allocate memory */
    [[nodiscard]] MemoryAllocation allocate(const MemoryAllocationModel &model);

    /** @brief Deallocate memory */
    void deallocate(const MemoryAllocation allocation);

    /** @brief Allocate a list of memory */
    [[nodiscard]] MemoryAllocation allocate(const std::vector<MemoryAllocationModel> &models);

    /** @brief Deallocate a list of memory */
    void deallocate(const std::vector<MemoryAllocation> &allocations);

private:
    /** @brief Create a memory allocator */
    void createMemoryAllocator(void);
};