/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: MemoryAllocation
 */

template<kF::Graphics::MemoryBindable Bindable, std::input_iterator Iterator>
inline kF::Graphics::MemoryAllocation kF::Graphics::MemoryAllocation::MakeStaging(const Bindable toBind, const Iterator dataBegin, const Iterator dataEnd)
{
    auto &allocator = Parent().memoryAllocator();
    MemoryAllocation allocation(MemoryAllocationModel::MakeStaging(toBind));

    auto mapped = allocator.beginMemoryMap<std::remove_cvref_t<decltype(*std::declval<Iterator>())>>(allocation);
    std::uninitialized_move(dataBegin, dataEnd, mapped);
    allocator.endMemoryMap(allocation);
    return allocation;
}