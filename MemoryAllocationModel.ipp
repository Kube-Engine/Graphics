/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: MemoryAllocationModel
 */

template<typename Type> requires std::same_as<Type, kF::Graphics::DeviceBuffer> || std::same_as<Type, kF::Graphics::DeviceImage>
kF::Graphics::MemoryAllocationModel::MemoryAllocationModel(const Type &value, const MemoryUsage usage) noexcept
    :   _usage(usage),
        _type(std::is_same_v<Type, DeviceBuffer> ? MemoryType::Buffer : MemoryType::Image)
{
    if constexpr (std::is_same_v<Type, DeviceBuffer>)
        _data.buffer = value;
    else
        _data.image = value;
}