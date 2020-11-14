/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: PipelineManager
 */

#include "Renderer.hpp"
#include "PipelineManager.hpp"

using namespace kF;

Graphics::PipelineHandle Graphics::PipelineManager::add(const PipelineModel &model)
{
    return _pipelines.push(model).handle();
}

void Graphics::PipelineManager::remove(const PipelineHandle pipeline) noexcept_ndebug
{
    const auto it = std::find_if(
        _pipelines.begin(), _pipelines.end(),
        [pipeline](const auto &it) { return it.handle() == pipeline; }
    );

    kFAssert(it != _pipelines.end(),
        throw std::runtime_error("Graphics::Renderer::removePipeline: Couldn't find pipeline"));
    _pipelines.erase(it);
}