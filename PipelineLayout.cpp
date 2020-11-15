/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: PipelineLayout
 */

#include <Kube/Core/StringLiteral.hpp>

#include "Renderer.hpp"
#include "PipelineLayout.hpp"

using namespace kF;
using namespace kF::Literal;

Graphics::PipelineLayout::~PipelineLayout(void)
{
    ::vkDestroyPipelineLayout(parent().logicalDevice(), handle(), nullptr);
}

void Graphics::PipelineLayout::createPipelineLayout(const PipelineLayoutModel &model)
{
    if (const auto res = ::vkCreatePipelineLayout(parent().logicalDevice(), &model, nullptr, &handle()); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::PipelineLayout::createPipelineLayout: Couldn't create pipeline layout '"s + ErrorMessage(res) + '\'');
}