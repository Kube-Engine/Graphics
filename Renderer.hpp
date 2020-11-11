/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Renderer interface
 */

#pragma once

#include "BackendWindow.hpp"
#include "Instance.hpp"
#include "Surface.hpp"
#include "PhysicalDevice.hpp"
#include "QueueManager.hpp"
#include "LogicalDevice.hpp"
#include "Swapchain.hpp"
#include "PipelinePool.hpp"
#include "RenderPass.hpp"
#include "FrameBufferManager.hpp"
#include "CommandPoolManager.hpp"
#include "BufferPool.hpp"
#include "Drawer.hpp"

namespace kF::Graphics
{
    class Renderer;
}

/** @brief Instance of the renderer tree, used to access the low-level GPU api */
class kF::Graphics::Renderer
{
public:
    /** @brief A queue of draw commands */
    using DrawQueue = std::vector<Command>;

    /** @brief Construct a renderer using a backend window */
    Renderer(BackendWindow *window, const Version applicationVersion = Version());

    /** @brief Move constructor */
    Renderer(Renderer &&renderer) noexcept = default;

    /** @brief Destruct the whole renderer tree */
    ~Renderer(void) = default;

    /** @brief Move assignment */
    Renderer &operator=(Renderer &&other) noexcept = default;


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

    /** @brief Get the pipeline pool */
    [[nodiscard]] PipelinePool &pipelinePool(void) noexcept { return _pipelinePool; }
    [[nodiscard]] const PipelinePool &pipelinePool(void) const noexcept { return _pipelinePool; }

    /** @brief Get the frameBuffer handler */
    [[nodiscard]] FrameBufferManager &frameBufferManager(void) noexcept { return _frameBufferManager; }
    [[nodiscard]] const FrameBufferManager &frameBufferManager(void) const noexcept { return _frameBufferManager; }

    /** @brief Get the command pool manager */
    [[nodiscard]] CommandPoolManager &commandPoolManager(void) noexcept { return _commandPoolManager; }
    [[nodiscard]] const CommandPoolManager &commandPoolManager(void) const noexcept { return _commandPoolManager; }


    /** @brief Get the number of cached frame */
    [[nodiscard]] std::size_t cachedFrameCount(void) const noexcept { return swapchain().imageViews().size(); }


    /** @brief Callback on render view size changed */
    void onViewSizeChanged(void);

private:
    BackendWindow *_window { nullptr };
    Instance _instance;
    Surface _surface;
    PhysicalDevice _physicalDevice;
    QueueManager _queueManager;
    LogicalDevice _logicalDevice;
    Swapchain _swapchain;
    RenderPass _renderPass;
    PipelinePool _pipelinePool;
    FrameBufferManager _frameBufferManager;
    CommandPoolManager _commandPoolManager;

    /** @brief Initialize the backend window for the renderer context */
    [[nodiscard]] static BackendWindow *InitializeContextWindow(void);
};