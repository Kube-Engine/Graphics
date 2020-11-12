/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: PipelineManager
 */

#include "Renderer.hpp"
#include "PipelineManager.hpp"

using namespace kF;

Graphics::PipelineHandle Graphics::PipelineManager::add(const PipelineModel &model)
{
    _models.push(std::make_unique<PipelineModel>(model));
    return _pipelines.push(parent(), model).handle();
}

void Graphics::PipelineManager::remove(const PipelineHandle pipeline) noexcept_ndebug
{
    const auto it = std::find_if(
        _pipelines.begin(), _pipelines.end(),
        [pipeline](const auto &it) { return it.handle() == pipeline; }
    );
    const auto mit = _models.begin() + std::distance(_pipelines.begin(), it);

    kFAssert(it != _pipelines.end(),
        throw std::runtime_error("Graphics::Renderer::removePipeline: Couldn't find pipeline"));
    _pipelines.erase(it);
    _models.erase(mit);
}

void Graphics::PipelineManager::onViewSizeChanged(void)
{
    _pipelines.clear();
    for (const auto &model : _models)
        _pipelines.push(parent(), *model);
}