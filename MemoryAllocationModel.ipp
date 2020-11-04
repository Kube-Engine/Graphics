/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: MemoryAllocationModel
 */

template<typename BufferType> requires std::same_as<BufferType, DeviceBuffer> || std::same_as<BufferType, DeviceImage>
kF::Graphics::MemoryAllocationModel::MemoryAllocationModel(const BufferType &buffer, const MemoryUsage usage) noexcept : 
    _data(type), 
    _usage(usage), 
    _type(std::is_same_v<Type, DeviceBuffer> ? MemoryType::Buffer : MemoryType::Image)
{

}