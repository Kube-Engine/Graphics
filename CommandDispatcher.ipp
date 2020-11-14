/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: CommandDispatcher
 */


inline void kF::Graphics::CommandDispatcher::addPresentDependencies(const QueueType queueType,
            const SemaphoreHandle * const semaphoreBegin, const SemaphoreHandle *semaphoreEnd,
            const FenceHandle * const fenceBegin, const FenceHandle *fenceEnd) noexcept
{
    auto &cache = _cachedFrames.currentCache();
    auto &semaphoreCache = cache.perQueueSemaphoreCache[static_cast<std::size_t>(queueType)];
    auto &fenceCache = cache.perQueueFenceCache[static_cast<std::size_t>(queueType)];

    semaphoreCache.insert(semaphoreCache.end(), semaphoreBegin, semaphoreEnd);
    fenceCache.insert(fenceCache.end(), fenceBegin, fenceEnd);
}