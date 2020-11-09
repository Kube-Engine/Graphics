/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: PipelinePool
 */

inline kF::Graphics::Pipeline &kF::Graphics::PipelinePool::getPipeline(const PipelineIndex index)
{
    auto it = findPipeline(index);

    if (it == _pipelineMap.end())
        throw std::runtime_error("Graphics::PipelinePool::getPipeline: Couldn't get pipeline of index '" + std::to_string(index) + '\'');
    return *it->second;
}

inline const kF::Graphics::Pipeline &kF::Graphics::PipelinePool::getPipeline(const PipelineIndex index) const
{
    auto it = findPipeline(index);

    if (it == _pipelineMap.end())
        throw std::runtime_error("Graphics::PipelinePool::getPipeline: Couldn't get pipeline of index '" + std::to_string(index) + '\'');
    return *it->second;
}