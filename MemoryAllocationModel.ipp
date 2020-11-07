/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: MemoryAllocationModel
 */

using namespace kF::Graphics;

template<typename Type> requires std::same_as<Type, DeviceBuffer> || std::same_as<Type, DeviceImage>
kF::Graphics::MemoryAllocationModel::MemoryAllocationModel(const Type &type, const MemoryUsage usage) noexcept : 
    _data(type), 
    _usage(usage), 
    _type(std::is_same_v<Type, DeviceBuffer> ? MemoryType::Buffer : MemoryType::Image)
{
    
}