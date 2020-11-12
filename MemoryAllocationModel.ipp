/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: MemoryAllocationModel
 */

template<kF::Graphics::MemoryBindable Type>
kF::Graphics::MemoryAllocationModel::MemoryAllocationModel(const Type &value, const MemoryUsage usage) noexcept
    :   _bindType(std::is_same_v<Type, BufferHandle> ? BindType::Buffer : BindType::Image),
        _usage(usage)
{
    if constexpr (std::is_same_v<Type, BufferHandle>)
        _data.buffer = value;
    else
        _data.image = value;
}