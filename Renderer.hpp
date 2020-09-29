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

namespace kF
{
    class Renderer;
}

class kF::Renderer
{
public:
    using DrawQueue = std::vector<Command>;

    Renderer(BackendWindow *window, const Version applicationVersion = Version());
    Renderer(Renderer &&renderer) = default;
    ~Renderer(void) = default;

    Renderer &operator=(Renderer &&other) = default;

    void draw(void);

    void onViewSizeChanged(void);

    [[nodiscard]] BackendWindow *getBackendWindow(void) const noexcept { return _window; }

    [[nodiscard]] Instance &getInstance(void) noexcept { return _instance; }
    [[nodiscard]] const Instance &getInstance(void) const noexcept { return _instance; }

    [[nodiscard]] Surface &getSurface(void) noexcept { return _surface; }
    [[nodiscard]] const Surface &getSurface(void) const noexcept { return _surface; }

    [[nodiscard]] PhysicalDevice &getPhysicalDevice(void) noexcept { return _physicalDevice; }
    [[nodiscard]] const PhysicalDevice &getPhysicalDevice(void) const noexcept { return _physicalDevice; }

    [[nodiscard]] QueueHandler &getQueueHandler(void) noexcept { return _queueHandler; }
    [[nodiscard]] const QueueHandler &getQueueHandler(void) const noexcept { return _queueHandler; }

    [[nodiscard]] LogicalDevice &getLogicalDevice(void) noexcept { return _logicalDevice; }
    [[nodiscard]] const LogicalDevice &getLogicalDevice(void) const noexcept { return _logicalDevice; }

    [[nodiscard]] Swapchain &getSwapchain(void) noexcept { return _swapchain; }
    [[nodiscard]] const Swapchain &getSwapchain(void) const noexcept { return _swapchain; }

    [[nodiscard]] RenderPass &getRenderPass(void) noexcept { return _renderPass; }
    [[nodiscard]] const RenderPass &getRenderPass(void) const noexcept { return _renderPass; }

    [[nodiscard]] PipelinePool &getPipelinePool(void) noexcept { return _pipelinePool; }
    [[nodiscard]] const PipelinePool &getPipelinePool(void) const noexcept { return _pipelinePool; }

    [[nodiscard]] FramebufferHandler &getFramebufferHandler(void) noexcept { return _framebufferHandler; }
    [[nodiscard]] const FramebufferHandler &getFramebufferHandler(void) const noexcept { return _framebufferHandler; }

    [[nodiscard]] CommandPool &getCommandPool(void) noexcept { return _commandPool; }
    [[nodiscard]] const CommandPool &getCommandPool(void) const noexcept { return _commandPool; }

    [[nodiscard]] BufferPool &getBufferPool(void) noexcept { return _bufferPool; }
    [[nodiscard]] const BufferPool &getBufferPool(void) const noexcept { return _bufferPool; }

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

    [[nodiscard]] static BackendWindow *InitializeContextWindow(void);
};