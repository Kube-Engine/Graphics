/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: DescriptorPool
 */

inline void kF::Graphics::DescriptorPool::allocateDescriptorSets(
        const kF::Graphics::DescriptorSetLayout * const layoutBengin, const kF::Graphics::DescriptorSetLayout * const layoutEnd,
        const kF::Graphics::DescriptorSet * descriptorSetBegin, const kF::Graphics::DescriptorSet * descriptorSetEnd)
{
    std::size_t len = 0u;
    if (len = std::distance(layoutBegin, layoutEnd); len != std::distance(descriptorSetBegin, descriptorSetEnd))
        throw std::runtime_error("Graphics::DescriptorPool::allocateDescriptorSets: Distance between descriptorSetBegin & descriptorSetEnd doesn't correspond to the input layouts distance !");

    VkDescriptorSetAllocateInfo allocInfo {
        sType: VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        pNext: nullptr,
        descriptorPool: handle(),
        descriptorSetCount: static_cast<std::uint32_t>(len),
        pSetLayouts: layoutBegin
    };

    if (auto res = ::vkAllocateDescriptorSets(parent().logicalDevice(), &allocInfo, descriptorSetBegin); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::DescriptorPool::allocateDescriptorSets: Couldn't allocate descriptor sets '"s + ErrorMessage(res) + '\'');
}
