/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: CommandDispatcher
 */


inline void kF::Graphics::CommandDispatcher::addPresentDependencies(const QueueType queueType,
        const SemaphoreHandle * const waitbegin, const SemaphoreHandle *waitEnd) noexcept
{
    auto &semaphoreCache = _cachedFrames.currentCache().perQueueSemaphoreCache[static_cast<std::size_t>(queueType)];

    semaphoreCache.insert(semaphoreCache.end(), waitbegin, waitEnd);
}