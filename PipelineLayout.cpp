/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: PipelineLayout
 */

#include "Renderer.hpp"

using namespace kF;

Graphics::PipelineLayout::~PipelineLayout(void)
{
    ::vkDestroyPipelineLayout(parent().logicalDevice(), handle(), nullptr);
}

void Graphics::PipelineLayout::createPipelineLayout(const PipelineLayoutModel &model)
{
    VkPipelineLayoutCreateInfo pipelineLayoutInfo {
        sType: VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        pNext: nullptr,
        flags: VkPipelineLayoutCreateFlags(),
        setLayoutCount: 0,
        pSetLayouts: nullptr,
        pushConstantRangeCount: 0,
        pPushConstantRanges: nullptr
    };

    if (auto res = ::vkCreatePipelineLayout(parent().logicalDevice(), &pipelineLayoutInfo, nullptr, &getPipelineLayout()); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::PipelineLayout::createPipelineLayout: Couldn't create pipeline layout '"s + ErrorMessage(res) + '\'');
}