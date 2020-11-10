/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: MemoryAllocationModel
 */

template<typename Type> requires std::same_as<Type, kF::Graphics::BufferHandle> || std::same_as<Type, kF::Graphics::ImageHandle>
kF::Graphics::MemoryAllocationModel::MemoryAllocationModel(const Type &value, const MemoryUsage usage) noexcept
    :   _data(value),
        _usage(usage),
        _type(std::is_same_v<Type, BufferHandle> ? MemoryType::Buffer : MemoryType::Image)
{
}