/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Thread safe command dispatcher for an efficient usage of hardware queues
 */

#pragma once

#include <thread>
#include <mutex>

#include "QueueHandler.hpp"

namespace kF
{
    class CommandDispatcher;
    class CommandPoolHandler;
}

/**
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

class kF::CommandPoolInstance
{
public:
    CommandPoolInstance(CommandDispatcher *parent, CommandPool *pool) : _parent(dispatcher), _pool(pool) {}
    CommandPoolInstance(CommandPoolInstance &&other) { swap(other); }
    ~CommandPoolInstance(void) {
        if (_pool)
            _parent->releaseInstance(_pool);
    }

    CommandPoolInstance &operator=(CommandPoolInstance &&other) { swap(other); }

    void swap(CommandPoolInstance &other) { std::swap(_parent, other._parent); std::swap(_pool, other._pool); }

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
class kF::CommandDispatcher : public RendererObject
{
public:
    CommandDispatcher(Renderer &renderer);
    CommandDispatcher(CommandDispatcher &&other) { swap(other); }
    ~CommandDispatcher(void);

    CommandDispatcher &operator=(CommandDispatcher &&other) noexcept { swap(other); return *this; }

    void swap(CommandDispatcher &other) { _pools.swap(other._pools); }

    [[nodiscard]] CommandPoolInstance reserveCommandPool(const QueueType type);
    void releaseInstance(CommandPool *pool);

    void onViewSizeChanged(void);

private:
    std::vector<std::unique_ptr<CommandPool>> _pools;
    std::mutex _poolsMutex;
};
