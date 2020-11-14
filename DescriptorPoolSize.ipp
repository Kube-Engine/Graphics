/**
 * @ Author: Pierre Veysseyre
 * @ Description: DescriptorPoolSize
 */

inline kF::Graphics::DescriptorPoolSize kF::Graphics::DescriptorPoolSize::MakeUniformBufferPoolSize(const std::uint32_t descriptorCount) noexcept
{
    return DescriptorPoolSize(DescriptorType::UniformBuffer, descriptorCount);
}
