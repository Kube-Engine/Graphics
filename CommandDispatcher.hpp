/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Thread safe command dispatcher for an efficient usage of hardware queues
 */

#pragma once

#include <thread>
#include <mutex>

#include "QueueHandler.hpp"

namespace kF::Graphics
{
    class CommandPoolInstance;
    class CommandDispatcher;
}

/** Notes for command pool usage best practises
 *
 * L * T + N pools
 * (L = the number of buffered frames,
 *  T = the number of threads which record command buffers,
 *  N = extra pools for secondary command buffers)
 *
 *  Reuse command pools for similarly sized sequences of draw calls.
 *      -> use 1 thread per task
 *  Call vkResetCommandPool before reusing it in another frame. Otherwise the pool will keep on growing until you run out of memory
 *  Don’t create/destroy command pools, reuse them instead. Save the overhead of allocator creation/destruction and memory allocation/free.
 *      -> Allocate pools as needed for each thread, don't destroy them if not specified explicitly
 *  Don’t forget that command pools consume GPU memory.
 *      -> Store an usage flag
 */

/** @brief This class holds an instance of command pool and its associated parent dispatcher */
class kF::Graphics::CommandPoolInstance
{
public:
    /** @brief Construct a command pool instance */
    CommandPoolInstance(CommandDispatcher *parent, CommandPool *pool) noexcept : _parent(parent), _pool(pool) {}

    /** @brief Move constructor */
    CommandPoolInstance(CommandPoolInstance &&other) noexcept { swap(other); }

    /** @brief Destructor, release the command pool instance */
    ~CommandPoolInstance(void);

    /** @brief Move assignment */
    CommandPoolInstance &operator=(CommandPoolInstance &&other) noexcept { swap(other); }

    /** @brief Swap two instances */
    void swap(CommandPoolInstance &other) noexcept { std::swap(_parent, other._parent); std::swap(_pool, other._pool); }

private:
    CommandDispatcher *_parent { nullptr };
    CommandPool *_pool { nullptr };
};

/*
 * API:
 *  CommandDispatcher should generate CommandPool objects on thread demands
 *
 * Usage:
 *  Make one ore more command buffer recorder for each thread
 *
 */
class kF::Graphics::CommandDispatcher : public RendererObject
{
public:
    /** @brief Construct the command dispatcher */
    CommandDispatcher(Renderer &renderer);

    /** @brief Move constructor */
    CommandDispatcher(CommandDispatcher &&other) noexcept { swap(other); }

    /** @brief Destruct the command dispatcher */
    ~CommandDispatcher(void);

    /** @brief Move assignment */
    CommandDispatcher &operator=(CommandDispatcher &&other) noexcept { swap(other); return *this; }

    /** @brief Swap two instances */
    void swap(CommandDispatcher &other) noexcept { _pools.swap(other._pools); }

    /** @brief Reserve a command pool */
    [[nodiscard]] CommandPoolInstance reserveCommandPool(const QueueType type);

    /** @brief Release a command pool */
    void releaseInstance(CommandPool *pool);

    /** @brief Callback on render view size changed */
    void onViewSizeChanged(void);

private:
    std::vector<std::unique_ptr<CommandPool>> _pools;
    std::mutex _poolsMutex;
};