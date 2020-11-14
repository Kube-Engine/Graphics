/**
 * @ Author: Pierre Veysseyre
 * @ Description: DescriptorSetLayoutModel
 */

template<typename ...Bindings>
    requires (... && std::is_same_as_v<Bindings, DescriptorSetLayoutBinding>)
inline kF::Graphics::DescriptorSetLayout kF::Graphics::DescriptorSetLayout::Make(Renderer &renderer,
        const DescriptorSetLayoutCreateFlags flags, Bindings &&...bindings) noexcept
{
    using Array = std::array<DescriptorSetLayoutBinding, sizeof...(Bindings)>;

    Array models { std::forward<Bindings>(bindings)... };

    return DescriptorSetLayout(
        renderer,
        DescriptorSetLayoutModel(
            flags,
            models.begin(), models.end()
        )
    );
}
