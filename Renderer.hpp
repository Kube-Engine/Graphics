/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Renderer interface
 */

#pragma once

#include <Kube/Core/TrivialDispatcher.hpp>

#include "BackendWindow.hpp"
#include "Instance.hpp"
#include "Surface.hpp"
#include "PhysicalDevice.hpp"
#include "QueueManager.hpp"
#include "LogicalDevice.hpp"
#include "Swapchain.hpp"
#include "RenderPass.hpp"
#include "FramebufferManager.hpp"
#include "CommandPoolManager.hpp"
#include "CommandDispatcher.hpp"
#include "MemoryAllocator.hpp"

namespace kF::Graphics
{
    class Renderer;
}

/** @brief Instance of the renderer tree, used to access the low-level GPU api */
class alignas_double_cacheline kF::Graphics::Renderer
{
public:
    /** @brief A renderer cannot be directly created, you must instead use GlobalInstance to handle its lifetime globally */
    class GlobalInstance
    {
    public:
        /** @brief Construct a global renderer using a backend window */
        GlobalInstance(BackendWindow * const window, const Version applicationVersion = Version());

        /** @brief Destroy the global renderer */
        ~GlobalInstance(void);

        /** @brief Access operator */
        [[nodiscard]] Renderer *operator->(void) noexcept { return _renderer; }
        [[nodiscard]] const Renderer *operator->(void) const noexcept { return _renderer; }

        /** @brief Dereference operator */
        [[nodiscard]] Renderer &operator*(void) noexcept { return *_renderer; }
        [[nodiscard]] const Renderer &operator*(void) const noexcept { return *_renderer; }

    private:
        Renderer *_renderer { nullptr };

        static inline bool _Constructed = false;
    };

    /** @brief Destruct the whole renderer tree */
    ~Renderer(void) = default;


    /** @brief Get the assigned backend window */
    [[nodiscard]] BackendWindow *backendWindow(void) const noexcept { return _window; }

    /** @brief Get the internal API instance */
    [[nodiscard]] Instance &instance(void) noexcept { return _instance; }
    [[nodiscard]] const Instance &instance(void) const noexcept { return _instance; }

    /** @brief Get the render surface */
    [[nodiscard]] Surface &surface(void) noexcept { return _surface; }
    [[nodiscard]] const Surface &surface(void) const noexcept { return _surface; }

    /** @brief Get the physical device */
    [[nodiscard]] PhysicalDevice &physicalDevice(void) noexcept { return _physicalDevice; }
    [[nodiscard]] const PhysicalDevice &physicalDevice(void) const noexcept { return _physicalDevice; }

    /** @brief Get the queue handler */
    [[nodiscard]] QueueManager &queueManager(void) noexcept { return _queueManager; }
    [[nodiscard]] const QueueManager &queueManager(void) const noexcept { return _queueManager; }

    /** @brief Get the logical device */
    [[nodiscard]] LogicalDevice &logicalDevice(void) noexcept { return _logicalDevice; }
    [[nodiscard]] const LogicalDevice &logicalDevice(void) const noexcept { return _logicalDevice; }

    /** @brief Get the swapchain */
    [[nodiscard]] Swapchain &swapchain(void) noexcept { return _swapchain; }
    [[nodiscard]] const Swapchain &swapchain(void) const noexcept { return _swapchain; }

    /** @brief Get the render pass */
    [[nodiscard]] RenderPass &renderPass(void) noexcept { return _renderPass; }
    [[nodiscard]] const RenderPass &renderPass(void) const noexcept { return _renderPass; }

    /** @brief Get the framebuffer handler */
    [[nodiscard]] FramebufferManager &framebufferManager(void) noexcept { return _framebufferManager; }
    [[nodiscard]] const FramebufferManager &framebufferManager(void) const noexcept { return _framebufferManager; }

    /** @brief Get the command pool manager */
    [[nodiscard]] CommandPoolManager &commandPoolManager(void) noexcept { return _commandPoolManager; }
    [[nodiscard]] const CommandPoolManager &commandPoolManager(void) const noexcept { return _commandPoolManager; }

    /** @brief Get the command dispatcher */
    [[nodiscard]] CommandDispatcher &commandDispatcher(void) noexcept { return _commandDispatcher; }
    [[nodiscard]] const CommandDispatcher &commandDispatcher(void) const noexcept { return _commandDispatcher; }

    /** @brief Get the memory allocator */
    [[nodiscard]] MemoryAllocator &memoryAllocator(void) noexcept { return _memoryAllocator; }
    [[nodiscard]] const MemoryAllocator &memoryAllocator(void) const noexcept { return _memoryAllocator; }


    /** @brief Get the number of cached frame */
    [[nodiscard]] std::size_t cachedFrameCount(void) const noexcept { return swapchain().imageCount(); }


    /** @brief Dispatch every known and registered 'onFrameAcquired' callback */
    void dispatchFrameAcquired(const FrameIndex frameIndex);

    /** @brief Dispatch every known and registered 'onViewSizeChanged' callback */
    void dispatchViewSizeChanged(void);


    /** @brief Get the 'onFrameAcquired' dispatcher */
    [[nodiscard]] auto &frameAcquiredDispatcher(void) noexcept { return _frameAcquiredDispatcher; }

    /** @brief Get the 'onViewSizeChanged' dispatcher */
    [[nodiscard]] auto &viewSizeDispatcher(void) noexcept { return _viewSizeDispatcher; }

private:
    BackendWindow *_window { nullptr };
    Instance _instance;
    Surface _surface {};
    PhysicalDevice _physicalDevice {};
    QueueManager _queueManager {};
    LogicalDevice _logicalDevice {};
    Swapchain _swapchain {};
    RenderPass _renderPass {};
    FramebufferManager _framebufferManager {};
    CommandPoolManager _commandPoolManager {};
    CommandDispatcher _commandDispatcher {};
    MemoryAllocator _memoryAllocator {};
    Core::TrivialDispatcher<void(const FrameIndex)> _frameAcquiredDispatcher {};
    Core::TrivialDispatcher<void(void)> _viewSizeDispatcher {};

    /** @brief Construct a renderer using a backend window */
    Renderer(BackendWindow * const window, const Version applicationVersion = Version());
};

static_assert_alignof_double_cacheline(kF::Graphics::Renderer);

#include "Renderer.ipp"