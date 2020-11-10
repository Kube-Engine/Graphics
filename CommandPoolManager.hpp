/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: CommandPoolManager
 */

#pragma once

#include <memory_resource>
#include <atomic>

#include "PerFrameCache.hpp"
#include "CommandPool.hpp"

namespace kF::Graphics
{
    class CommandPoolManager;
}

/** @brief Manager of every command pool
 *  'acquire' and 'takeBack' functions are the only thread safe ones
 *
 *  Manager is used to acquire access to an auto command pool for a given frame: each command is one time submit
 *  If you wish to reuse command buffers, please use a ManualCommandPool instead of the CommandPoolManager
 */
class alignas_cacheline kF::Graphics::CommandPoolManager final : public RendererObject
{
public:
    /** @brief Pool node */
    struct Node;

    /** @brief An atomic pool node */
    using AtomicNode = std::atomic<Node *>;

    /** @brief An array of pools sorted by queue types */
    using PerQueueNodeArray = std::array<AtomicNode, static_cast<std::size_t>(QueueType::Count)>;

    /** @brief Command pool node */
    struct Node
    {
        AutoCommandPool pool;
        Node *next { nullptr };
    };

    /** @brief This class allow to use a command pool in its scope before releasing it in the manager */
    class ScopedCommandPool
    {
    public:
        /** @brief Default constructor */
        ScopedCommandPool(void) noexcept = default;

        /** @brief Acquire constructor */
        ScopedCommandPool(Node * const node, CommandPoolManager * const manager) noexcept
            : _node(node), _manager(manager) {}

        /** @brief Move constructor */
        ScopedCommandPool(ScopedCommandPool &&other) noexcept { swap(other); }

        /** @brief Release destructor */
        ~ScopedCommandPool(void) noexcept { release(); }

        /** @brief Move assignment */
        ScopedCommandPool &operator=(ScopedCommandPool &&other) noexcept { swap(other); return *this; }

        /** @brief Swap two instances */
        void swap(ScopedCommandPool &other) noexcept
            { std::swap(_node, other._node); std::swap(_manager, other._manager); }

        /** @brief Fast empty check */
        [[nodiscard]] operator bool(void) const noexcept { return _node; }

        /** @brief Get internal pool */
        [[nodiscard]] AutoCommandPool *operator->(void) noexcept { return &_node->pool; }
        [[nodiscard]] const AutoCommandPool *operator->(void) const noexcept { return &_node->pool; }

        /** @brief Release the acquired pool */
        void release(void) noexcept;

    private:
        Node *_node { nullptr };
        CommandPoolManager *_manager { nullptr };
    };


    /** @brief Contruct the manager */
    CommandPoolManager(Renderer &renderer) = default;

    /** @brief Move constructor, not thread safe */
    CommandPoolManager(CommandPoolManager &&other) noexcept = default;

    /** @brief Destruct the manager and every pool, not thread safe */
    ~CommandPoolManager(void) = default;

    /** @brief Move assignment, not thread safe */
    CommandPoolManager &operator=(CommandPoolManager &&other) noexcept = default;


    /** @brief Acquire a scoped command pool in the current frame context, thread safe */
    [[nodiscard]] ScopedCommandPool acquire(const QueueType type);

    /** @brief Take ownership of a previously acquired node (called in ScopedCommandPool), thread safe */
    void takeBack(Node *node) noexcept;


    /** @brief Acquire the next frame without releasing current one, not thread safe */
    void acquireNextFrame(void) noexcept_ndebug;

    /** @brief Release a given frame, not thread safe */
    void releaseFrame(const FrameIndex frameIndex) noexcept;

private:
    static inline std::pmr::synchronized_pool_resource _Allocator {};

    PerFrameCache<PerQueueNodeArray> _cachedFrames;
#if KUBE_DEBUG_BUILD
    std::atomic<std::size_t> _activeScopedCount { 0u };
#endif

    /** @brief Allocate and construct a new node using allocator */
    [[nodiscard]] Node *allocate(const QueueType queueType) noexcept;

    /** @brief Destruct and deallocate a node using allocator */
    [[nodiscard]] Node *deallocate(Node * const node) noexcept;
};

static_assert_fit_cacheline(kF::Graphics::CommandPoolManager);

#include "CommandPoolManager.ipp"