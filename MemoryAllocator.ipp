/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: MemoryAllocator
 */

inline kF::Graphics::MemoryAllocation kF::Graphics::MemoryAllocator::allocate(const MemoryAllocationModel &model)
{
    MemoryAllocation allocation;

    allocate(&model, &model + 1, &allocation, &allocation + 1);
    return allocation;
}

inline void kF::Graphics::MemoryAllocator::deallocate(const MemoryAllocation allocation)
{
    deallocate(&allocation, &allocation + 1);
}