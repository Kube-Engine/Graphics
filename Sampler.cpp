/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Sampler
 */

#include <Kube/Core/StringLiteral.hpp>

#include "Renderer.hpp"
#include "Sampler.hpp"

using namespace kF;
using namespace kF::Literal;

Graphics::Sampler::~Sampler(void) noexcept
{
    ::vkDestroySampler(parent().logicalDevice(), handle(), nullptr);
}

void Graphics::Sampler::createSampler(const SamplerModel &model)
{
    if (const auto res = ::vkCreateSampler(parent().logicalDevice(), &model, nullptr, &handle()); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::Sampler::createSampler: Couldn't create sampler '"s + ErrorMessage(res) + '\'');
}