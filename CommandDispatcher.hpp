/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: CommandDispatcher
 */

#pragma once

#include "PerFrameCache.hpp"
#include "CommandPool.hpp"

namespace kF::Graphics
{
    class CommandPoolInstance;
    class CommandDispatcher;
}

/** @brief Command dispatcher collect commands and dispatch them later */
class kF::Graphics::CommandDispatcher : public RendererObject
{
public:
    /** @brief An array of command sorted by queue types */
    struct alignas_double_cacheline PerQueueCommandArray
    {
        using Commands = Core::TinyVector<CommandHandle>;
        using Array = std::array<Commands, static_cast<std::size_t>(QueueType::Count)>;

        alignas(Commands) Array array;
#if KUBE_DEBUG_BUILD
        bool cleared { true };
#endif
    };

    /** @brief Construct the command dispatcher */
    CommandDispatcher(Renderer &renderer) noexcept : RendererObject(renderer), _cachedFrames(renderer.cachedFrameCount()) {}

    /** @brief Move constructor */
    CommandDispatcher(CommandDispatcher &&other) noexcept = default;

    /** @brief Destruct the command dispatcher */
    ~CommandDispatcher(void) noexcept = default;

    /** @brief Move assignment */
    CommandDispatcher &operator=(CommandDispatcher &&other) noexcept { swap(other); return *this; }

    /** @brief Swap two instances */
    void swap(CommandDispatcher &other) noexcept;


    /** @brief Prepare a single command to be dispatcher in a specific queue */
    void prepare(const QueueType queueType, const CommandHandle command) noexcept
        { prepare(queueType, &command, &command + 1); }

    /** @brief Prepare a set of commands of the same queue type to be dispatched */
    void prepare(const QueueType queueType, const CommandHandle * const from, const CommandHandle * const to) noexcept;


    /** @brief Dispatch all cached commands of a same queue (only thread safe if the underlying hardward queue is not already submitting) */
    void dispatch(const QueueType queueType);


    /** @brief Acquire the next frame without releasing current one */
    void acquireNextFrame(void) noexcept_ndebug;

    /** @brief Release a given frame */
    void releaseFrame(const FrameIndex frameIndex) noexcept;


    /** @brief Clear every cached command of every frame */
    void clear(void) noexcept;


    /** @brief Callback on render view size changed */
    void onViewSizeChanged(void) noexcept { clear(); }

private:
    PerFrameCache<PerQueueCommandArray> _cachedFrames;
};

#include "CommandDispatcher.ipp