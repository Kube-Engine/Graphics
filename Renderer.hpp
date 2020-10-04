/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Renderer interface
 */

#pragma once

#include "BackendWindow.hpp"
#include "Instance.hpp"
#include "Surface.hpp"
#include "PhysicalDevice.hpp"
#include "QueueHandler.hpp"
#include "LogicalDevice.hpp"
#include "Swapchain.hpp"
#include "PipelinePool.hpp"
#include "RenderPass.hpp"
#include "FramebufferHandler.hpp"
#include "CommandPool.hpp"
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

    /** @brief Execute the drawer to present a frame */
    void draw(void);

    /** @brief Callback on render view size changed */
    void onViewSizeChanged(void);

    /** @brief Get the assigned backend window */
    [[nodiscard]] BackendWindow *getBackendWindow(void) const noexcept { return _window; }

    /** @brief Get the internal API instance */
    [[nodiscard]] Instance &getInstance(void) noexcept { return _instance; }
    [[nodiscard]] const Instance &getInstance(void) const noexcept { return _instance; }

    /** @brief Get the render surface */
    [[nodiscard]] Surface &getSurface(void) noexcept { return _surface; }
    [[nodiscard]] const Surface &getSurface(void) const noexcept { return _surface; }

    /** @brief Get the physical device */
    [[nodiscard]] PhysicalDevice &getPhysicalDevice(void) noexcept { return _physicalDevice; }
    [[nodiscard]] const PhysicalDevice &getPhysicalDevice(void) const noexcept { return _physicalDevice; }

    /** @brief Get the queue handler */
    [[nodiscard]] QueueHandler &getQueueHandler(void) noexcept { return _queueHandler; }
    [[nodiscard]] const QueueHandler &getQueueHandler(void) const noexcept { return _queueHandler; }

    /** @brief Get the logical device */
    [[nodiscard]] LogicalDevice &getLogicalDevice(void) noexcept { return _logicalDevice; }
    [[nodiscard]] const LogicalDevice &getLogicalDevice(void) const noexcept { return _logicalDevice; }

    /** @brief Get the swapchain */
    [[nodiscard]] Swapchain &getSwapchain(void) noexcept { return _swapchain; }
    [[nodiscard]] const Swapchain &getSwapchain(void) const noexcept { return _swapchain; }

    /** @brief Get the render pass */
    [[nodiscard]] RenderPass &getRenderPass(void) noexcept { return _renderPass; }
    [[nodiscard]] const RenderPass &getRenderPass(void) const noexcept { return _renderPass; }

    /** @brief Get the pipeline pool */
    [[nodiscard]] PipelinePool &getPipelinePool(void) noexcept { return _pipelinePool; }
    [[nodiscard]] const PipelinePool &getPipelinePool(void) const noexcept { return _pipelinePool; }

    /** @brief Get the framebuffer handler */
    [[nodiscard]] FramebufferHandler &getFramebufferHandler(void) noexcept { return _framebufferHandler; }
    [[nodiscard]] const FramebufferHandler &getFramebufferHandler(void) const noexcept { return _framebufferHandler; }

    /** @brief Get the command pool */
    [[nodiscard]] CommandPool &getCommandPool(void) noexcept { return _commandPool; }
    [[nodiscard]] const CommandPool &getCommandPool(void) const noexcept { return _commandPool; }

    /** @brief Get the buffer pool */
    [[nodiscard]] BufferPool &getBufferPool(void) noexcept { return _bufferPool; }
    [[nodiscard]] const BufferPool &getBufferPool(void) const noexcept { return _bufferPool; }

    /** @brief Get the renderer drawer */
    [[nodiscard]] Drawer &getDrawer(void) noexcept { return _drawer; }
    [[nodiscard]] const Drawer &getDrawer(void) const noexcept { return _drawer; }

private:
    BackendWindow *_window = nullptr;
    Instance _instance;
    Surface _surface;
    PhysicalDevice _physicalDevice;
    QueueHandler _queueHandler;
    LogicalDevice _logicalDevice;
    Swapchain _swapchain;
    RenderPass _renderPass;
    PipelinePool _pipelinePool;
    FramebufferHandler _framebufferHandler;
    CommandPool _commandPool;
    BufferPool _bufferPool;
    Drawer _drawer;

    /** @brief Initialize the backend window for the renderer context */
    [[nodiscard]] static BackendWindow *InitializeContextWindow(void);
};