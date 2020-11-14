/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: CommandDispatcher
 */

#pragma once

#include "Semaphore.hpp"
#include "Fence.hpp"
#include "SubmitInfo.hpp"
#include "CommandPool.hpp"

namespace kF::Graphics
{
    class CommandPoolInstance;
    class CommandDispatcher;
}

/** @brief Command dispatcher collect commands and dispatch them later */
class alignas_double_cacheline kF::Graphics::CommandDispatcher : public CachedRendererObject
{
public:
    static constexpr auto QueueCount = static_cast<std::size_t>(QueueType::Count);

    /** @brief Cache of semaphore handle */
    using SemaphoreCache = Core::TinyVector<SemaphoreHandle>;

    /** @brief Cache of fence handle */
    using FenceCache = Core::TinyVector<FenceHandle>;

    /** @brief An array of command sorted by queue types */
    struct alignas_cacheline FrameCache
    {
        std::array<SemaphoreCache, QueueCount> _perQueueSemaphoreCache {};
        std::array<FenceCache, QueueCount> _perQueueFenceCache {};
        SemaphoreCache _semaphoreCache {};
        FenceCache _fenceCache {};
        Semaphore _frameAvailable;
    };

    static_assert_alignof_cacheline(FrameCache);

    /** @brief Construct the command dispatcher */
    CommandDispatcher(void) noexcept;

    /** @brief Move constructor */
    CommandDispatcher(CommandDispatcher &&other) noexcept = default;

    /** @brief Destruct the command dispatcher */
    ~CommandDispatcher(void) noexcept = default;

    /** @brief Move assignment */
    CommandDispatcher &operator=(CommandDispatcher &&other) noexcept = default;


    /** @brief Dispatch commands of a given queue (only thread safe if the underlying hardward queue is not already submitting) */
    void dispatch(const QueueType queueType, const SubmitInfo * const submitBegin, const SubmitInfo * const submitEnd, const FenceHandle fence);


    /** @brief Try to acquire the next frame */
    [[nodiscard]] bool tryAcquireNextFrame(void);


    /** @brief Prepare current presentation */
    void presentFrame(void);


    /** @brief Clear every cached command of every frame */
    void clear(void) noexcept;

private:
    PerFrameCache<FrameCache> _cachedFrames;
};

static_assert_fit_double_cacheline(kF::Graphics::CommandDispatcher);

#include "CommandDispatcher.ipp"