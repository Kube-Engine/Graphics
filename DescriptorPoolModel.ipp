/**
 * @ Author: Pierre Veysseyre
 * @ Description: DescriptorPoolModel implementation
 */

inline kF::Graphics::DescriptorPoolModel kF::Graphics::DescriptorPoolModel::MakeUniformBufferPool(const std::uint32_t maxSets, const DescriptorPoolSize &poolSize) noexcept
{
    return DescriptorPoolModel(
        DescriptorSetLayoutCreateFlags::None,
        maxSets,
        &poolSize,
        &poolSize + 1
    );
}

inline kF::Graphics::DescriptorPoolModel kF::Graphics::DescriptorPoolModel::MakeUniformBufferPool(const std::uint32_t maxSets,
        const DescriptorPoolSize *poolSizeBegin, const DescriptorPoolSize *poolSizeEnd) noexcept
{
    return DescriptorPoolModel(
        DescriptorSetLayoutCreateFlags::None,
        maxSets,
        poolSizeBegin,
        poolSizeEnd
    );
}
