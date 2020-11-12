/**
 * @ Author: Pierre Veysseyre
 * @ Description: DescriptorModel.ipp
 */

inline kF::Graphics::DescriptorModel kF::Graphics::DescriptorModel::MakeUniqueUniformBuffer(const uint32_t binding, const ShaderStageFlags shaderStage) noexcept
{
    return DescriptorModel(
        DescriptorSetLayoutCreateFlags::None,
        DescriptorBindingModel(
            binding,
            DescriptorType::UniformBuffer,
            1,
            shaderStage
        )
    );
    // return DescriptorModel(
    //     DescriptorSetLayoutCreateFlags::None,
    //     {
    //         DescriptorBindingModel(
    //             0,
    //             DescriptorType::UniformBuffer,
    //             1,
    //             shaderStage
    //         ),
    //         DescriptorBindingModel(
    //             1,
    //             DescriptorType::UniformBuffer,
    //             1,
    //             shaderStage
    //         )
    //     }
    // );
}
