/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: MemoryAllocator
 */

inline kF::Graphics::MemoryAllocationHandle kF::Graphics::MemoryAllocator::allocate(const MemoryAllocationModel &model)
{
    MemoryAllocationHandle allocation;

    allocate(&model, &model + 1, &allocation, &allocation + 1);
    return allocation;
}

template<typename Type>
inline Type *kF::Graphics::MemoryAllocator::beginMemoryMap(const MemoryAllocationHandle allocation) const
{
    void *target { nullptr };
    if (const auto res = ::vmaMapMemory(handle(), allocation, &target); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::MemoryAllocator::beginMemoryMap: Couldn't map allocation memory '" + std::string(ErrorMessage(res)) + '\'');
    return reinterpret_cast<Type *>(target);
}

inline void kF::Graphics::MemoryAllocator::endMemoryMap(const MemoryAllocationHandle allocation) const
{
    ::vmaUnmapMemory(handle(), allocation);
}