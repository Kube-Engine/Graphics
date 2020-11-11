/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: MemoryAllocator
 */

inline kF::Graphics::MemoryAllocationHandle kF::Graphics::MemoryAllocator::allocate(const MemoryAllocationHandleModel &model)
{
    MemoryAllocationHandle allocation;

    allocate(&model, &model + 1, &allocation, &allocation + 1);
    return allocation;
}

inline void kF::Graphics::MemoryAllocator::deallocate(const MemoryAllocationHandle allocation)
{
    deallocate(&allocation, &allocation + 1);
}