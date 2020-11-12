/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Pipeline
 */

#include <Kube/Core/StringLiteral.hpp>

#include "Renderer.hpp"
#include "Pipeline.hpp"

using namespace kF;
using namespace kF::Literal;

Graphics::Pipeline::~Pipeline(void) noexcept
{
    ::vkDestroyPipeline(parent().logicalDevice(), handle(), nullptr);
}

void Graphics::Pipeline::createPipeline(const PipelineModel &model)
{
    if (auto res = ::vkCreateGraphicsPipelines(parent().logicalDevice(), VkPipelineCache(), 1u, &model, nullptr, &handle()); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::Pipeline::createPipeline: Couldn't create pipeline '"s + ErrorMessage(res) + '\'');
}