/**
 * @ Author: Pierre Veysseyre
 * @ Description: DescriptorSetLayoutModel
 */

template<typename ...Bindings>
    requires (... && std::is_same_v<Bindings, kF::Graphics::DescriptorSetLayoutBinding>)
inline kF::Graphics::DescriptorSetLayout kF::Graphics::DescriptorSetLayout::Make(
        const DescriptorSetLayoutCreateFlags flags, Bindings &&...bindings) noexcept
{
    using Array = std::array<DescriptorSetLayoutBinding, sizeof...(Bindings)>;

    Array models { std::forward<Bindings>(bindings)... };

    return DescriptorSetLayout(
        DescriptorSetLayoutModel(
            flags,
            models.begin(), models.end()
        )
    );
}
