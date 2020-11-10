/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: PipelinePool
 */

#include <algorithm>

#include "Renderer.hpp"

using namespace kF;
using namespace kF::Literal;

Graphics::PipelineIndex Graphics::PipelinePool::addPipeline(const PipelineModel &model)
{
    auto index = 1u;

    if (!_pipelineMap.empty())
        index = _pipelineMap.crbegin()->first + 1;
    _pipelineMap.emplace_back(index, std::make_unique<Pipeline>(Pipeline(parent(), model)));
    _modelMap.emplace_back(index, std::make_unique<PipelineModel>(model));
    return index;
}

void Graphics::PipelinePool::removePipeline(const PipelineIndex index)
{
    auto it = findPipeline(index);

    if (it == _pipelineMap.end())
        throw std::runtime_error("Graphics::Renderer::removePipeline: Couldn't find pipeline with index '" + std::to_string(index) + '\'');
    _pipelineMap.erase(it);
    auto mit = _modelMap.begin() + std::distance(_pipelineMap.begin(), it);
    _modelMap.erase(mit);
}

void Graphics::PipelinePool::onViewSizeChanged(void)
{
    for (auto it = _modelMap.begin(); auto &pair : _pipelineMap) {
        *pair.second = Pipeline(parent(), *it->second);
        ++it;
    }
}