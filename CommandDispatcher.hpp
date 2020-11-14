/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: CommandDispatcher
 */

#pragma once

#include <optional>

#include "PerFrameCache.hpp"
#include "Semaphore.hpp"
#include "Fence.hpp"
#include "SubmitInfo.hpp"
#include "CommandPool.hpp"

namespace kF::Graphics
{
    class CommandDispatcher;
}

/** @brief Command dispatcher collect commands and dispatch them later */
class alignas_cacheline kF::Graphics::CommandDispatcher : public CachedRendererObject
{
public:
    /** @brief Cache of semaphore handle */
    using SemaphoreCache = Core::TinyVector<SemaphoreHandle>;

    /** @brief Cache of fence handle */
    using FenceCache = Core::TinyVector<FenceHandle>;

    /** @brief An array of command sorted by queue types */
    struct alignas_double_cacheline FrameCache
    {
        std::array<SemaphoreCache, QueueCount> perQueueSemaphoreCache {};
        std::array<FenceCache, QueueCount> perQueueFenceCache {};
        SemaphoreCache semaphoreCache {};
        FenceCache fenceCache {};
        std::optional<Semaphore> frameAvailable {};

        FrameCache(void) noexcept = default; // Default constructor not existing, optional bug ?
    };

    static_assert_alignof_double_cacheline(FrameCache);
    static_assert_sizeof(FrameCache, Core::CacheLineSize * 4);


    /** @brief Construct the command dispatcher */
    CommandDispatcher(void) noexcept;

    /** @brief Move constructor */
    CommandDispatcher(CommandDispatcher &&other) noexcept = default;

    /** @brief Destruct the command dispatcher */
    ~CommandDispatcher(void) noexcept = default;

    /** @brief Move assignment */
    CommandDispatcher &operator=(CommandDispatcher &&other) noexcept = default;


    /** @brief Get the frame available semaphore of the current frame */
    [[nodiscard]] SemaphoreHandle currentFrameAvailableSemaphore(void) const noexcept { return _cachedFrames.currentCache().frameAvailable.value().handle(); }

    /** @brief Dispatch commands of a given queue (only thread safe if the underlying hardward queue is not already submitting) */
    void dispatch(const QueueType queueType, const SubmitInfo * const submitBegin, const SubmitInfo * const submitEnd,
            const FenceHandle fence);

    /** @brief Add dependencies to presentation of current frame (thread safe for different queue type calls) */
    void addPresentDependencies(const QueueType queueType,
            const SemaphoreHandle * const semaphoreBegin, const SemaphoreHandle *semaphoreEnd,
            const FenceHandle * const fenceBegin, const FenceHandle *fenceEnd) noexcept;


    /** @brief Try to acquire the next frame */
    [[nodiscard]] bool tryAcquireNextFrame(void);

    /** @brief Prepare current presentation */
    void presentFrame(void);


    /** @brief Clear everything */
    void clear(void) noexcept;

    /** @brief Clear every cached command of every frame */
    void onViewSizeChanged(void) noexcept { clear(); }

private:
    Core::TinyVector<Semaphore> _availableSemaphores {};
    PerFrameCache<FrameCache> _cachedFrames;
};

static_assert_fit_cacheline(kF::Graphics::CommandDispatcher);

#include "CommandDispatcher.ipp"