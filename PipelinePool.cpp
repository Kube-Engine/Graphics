/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: PipelinePool
 */

#include <algorithm>

#include "Renderer.hpp"

using namespace kF;
using namespace kF::Literal;

Graphics::PipelinePool::PipelinePool(Renderer &renderer)
    : RendererObject(renderer)
{
}

Graphics::PipelineIndex Graphics::PipelinePool::addPipeline(const PipelineModel &model)
{
    auto index = 1u;

    if (!_pipelineMap.empty())
        index = _pipelineMap.crbegin()->first + 1;
    _pipelineMap.emplace_back(index, std::make_unique<Pipeline>(Pipeline(parent(), model)));
#ifndef KUBE_HAS_DYNAMIC_WINDOW_RESIZE
    _modelMap.emplace_back(index, std::make_unique<PipelineModel>(model));
#endif
    return index;
}

void Graphics::PipelinePool::removePipeline(const PipelineIndex index)
{
    auto it = findPipeline(index);

    if (it == _pipelineMap.end())
        throw std::runtime_error("Renderer::removePipeline: Couldn't find pipeline with index '" + std::to_string(index) + '\'');
    _pipelineMap.erase(it);
#ifndef KUBE_HAS_DYNAMIC_WINDOW_RESIZE
    auto mit = _modelMap.begin() + std::distance(_pipelineMap.begin(), it);
    _modelMap.erase(mit);
#endif
}

Graphics::Pipeline &Graphics::PipelinePool::getPipeline(const PipelineIndex index)
{
    auto it = findPipeline(index);

    if (it == _pipelineMap.end())
        throw std::runtime_error("Graphics::PipelinePool::getPipeline: Couldn't get pipeline of index '" + std::to_string(index) + '\'');
    return *it->second;
}

const Graphics::Pipeline &Graphics::PipelinePool::getPipeline(const PipelineIndex index) const
{
    auto it = findPipeline(index);

    if (it == _pipelineMap.end())
        throw std::runtime_error("Graphics::PipelinePool::getPipeline: Couldn't get pipeline of index '" + std::to_string(index) + '\'');
    return *it->second;
}

void Graphics::PipelinePool::onViewSizeChanged(void)
{
#ifndef KUBE_HAS_DYNAMIC_WINDOW_RESIZE
    for (auto it = _modelMap.begin(); auto &pair : _pipelineMap) {
        *pair.second = Pipeline(parent(), *it->second);
        ++it;
    }
#endif
}