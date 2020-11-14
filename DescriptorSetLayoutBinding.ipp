/**
 * @ Author: Pierre Veysseyre
 * @ Description: DescriptorSetLayoutBinding implementation
 */

inline kF::Graphics::DescriptorSetLayoutBinding kF::Graphics::DescriptorSetLayoutBinding::MakeUniformBinding(
        const std::uint32_t binding, const std::uint32_t descriptorCount, const ShaderStageFlags shaderStageFlags) noexcept
{
    return DescriptorSetLayoutBinding(
        binding,
        DescriptorType::UniformBuffer,
        descriptorCount,
        shaderStageFlags,
        nullptr
    );
}
