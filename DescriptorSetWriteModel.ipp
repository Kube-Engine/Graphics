/**
 * @ Author: Pierre Veysseyre
 * @ Description: DescriptorSetWriteModel implementation
 */

inline kF::Graphics::DescriptorSetWriteModel kF::Graphics::DescriptorSetWriteModel::MakeBufferWriteModel(
        kF::Graphics::DescriptorSet &descriptorSet, const std::uint32_t dstBinding, const kF::Graphics::DescriptorType descriptorType,
        const kF::Graphics::DescriptorBufferInfo * const bufferInfoBegin, const kF::Graphics::DescriptorBufferInfo * const bufferInfoEnd) noexcept
{
    return DescriptorSetWriteModel(
        descriptorSet,
        dstBinding,
        0,
        static_cast<std::uint32_t>(std::distance(bufferInfoBegin, bufferInfoEnd)),
        descriptorType,
        nullptr,
        bufferInfoBegin,
        nullptr
    );
};

inline kF::Graphics::DescriptorSetWriteModel kF::Graphics::DescriptorSetWriteModel::MakeImageWriteModel(
        kF::Graphics::DescriptorSet &descriptorSet, const std::uint32_t dstBinding, const kF::Graphics::DescriptorType descriptorType,
        const kF::Graphics::DescriptorImageInfo * const imageInfoBegin, const kF::Graphics::DescriptorImageInfo * const imageInfoEnd) noexcept
{
    return DescriptorSetWriteModel(
        descriptorSet,
        dstBinding,
        0,
        static_cast<std::uint32_t>(std::distance(imageInfoBegin, imageInfoEnd)),
        descriptorType,
        imageInfoBegin,
        nullptr,
        nullptr
    );
};

inline kF::Graphics::DescriptorSetWriteModel kF::Graphics::DescriptorSetWriteModel::MakeTexelWriteModel(
        kF::Graphics::DescriptorSet &descriptorSet, const std::uint32_t dstBinding, const kF::Graphics::DescriptorType descriptorType,
        const kF::Graphics::BufferViewHandle * const bufferViewBegin, const kF::Graphics::BufferViewHandle * const bufferViewEnd) noexcept
{
    return DescriptorSetWriteModel(
        descriptorSet,
        dstBinding,
        0,
        static_cast<std::uint32_t>(std::distance(bufferViewBegin, bufferViewEnd)),
        descriptorType,
        nullptr,
        nullptr
        bufferViewBegin,
    );
};
