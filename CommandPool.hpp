/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: CommandPool
 */

#pragma once

#include <Kube/Core/Vector.hpp>

#include "QueueManager.hpp"
#include "CommandModel.hpp"

namespace kF::Graphics
{
    class CommandPool;
    class ManualCommandPool;
    class AutoCommandPool;
}

/** @brief Command pool that allocates command buffers */
class alignas_half_cacheline kF::Graphics::CommandPool : public VulkanHandle<VkCommandPool>
{
public:
    /** @brief Lifecycle of commands inside the pool */
    enum class Lifecycle {
        Manual,
        Auto
    };


    /** @brief Construct the command pool */
    CommandPool(Renderer &renderer, const QueueType queueType, const Lifecycle lifecycle);

    /** @brief Move constructor */
    CommandPool(CommandPool &&other) noexcept = default;

    /** @brief Destruct the command pool */
    ~CommandPool(void) noexcept_ndebug;

    /** @brief Move assignment */
    CommandPool &operator=(CommandPool &&other) noexcept = default;


    /** @brief Adds a command to the pool */
    template<CommandModel Model>
    [[nodiscard]] CommandHandle add(const Model &model, const CommandLevel level, const Lifecycle lifecycle);

    /** @brief Adds a range of commands to the pool
     *  If the number of models is 1 (modelTo - modelFrom), we duplicate the command for each output commands (commandTo - commandFrom) */
    template<CommandModel Model>
    void add(const Model * const modelFrom, const Model * const modelTo,
            CommandHandle * const commandFrom, CommandHandle * const commandTo,
            const CommandLevel level, const Lifecycle lifecycle);

    /** @brief Remove a command from the pool */
    void remove(const CommandHandle command) noexcept { remove(&command, &command + 1); }

    /** @brief Remove a range commands from the pool */
    void remove(const CommandHandle * const from, const CommandHandle * const to) noexcept;

    /** @brief Clear every commands at once */
    void clear(void) noexcept;


    /** @brief Get the queue level used by the pool */
    [[nodiscard]] QueueType queueType(void) const noexcept { return _queueType; }

private:
    QueueType _queueType { QueueType::Graphics };

    /** @brief Create a command pool */
    void createCommandPool(const QueueType queueType, const Lifecycle lifecycle);

    /** @brief Allocate multiple command buffers */
    void allocateCommands(CommandHandle * const commandFrom, CommandHandle * const commandTo, const CommandLevel level);

    /** @brief Record render commands */
    void recordRender(const RenderModel * const modelFrom, const RenderModel * const modelTo,
            CommandHandle * const commandFrom, CommandHandle * const commandTo,
            const VkCommandBufferBeginInfo &commandBeginInfo);

    /** @brief Record transfer commands */
    void recordTransfer(const TransferModel * const modelFrom, const TransferModel * const modelTo,
            CommandHandle * const commandFrom, CommandHandle * const commandTo,
            const VkCommandBufferBeginInfo &commandBeginInfo);

    /** @brief Helper toretreive command usage flags out of lifecycle */
    [[nodiscard]] static VkCommandBufferUsageFlags GetCommandUsageFlags(const Lifecycle lifecycle);
};

static_assert_fit_half_cacheline(kF::Graphics::CommandPool);

/** @brief A command pool that can only create one time submit commands */
class kF::Graphics::AutoCommandPool : public CommandPool
{
public:
    /** @brief Construct the command pool */
    AutoCommandPool(Renderer &renderer, const QueueType queueType) : CommandPool(renderer, queueType, Lifecycle::Auto) {}

    /** @brief Move constructor */
    AutoCommandPool(AutoCommandPool &&other) noexcept = default;

    /** @brief Destruct the command pool */
    ~AutoCommandPool(void) noexcept = default;

    /** @brief Move assignment */
    AutoCommandPool &operator=(AutoCommandPool &&other) noexcept = default;


    /** @brief Add a one time submit command */
    template<CommandModel Model>
    [[nodiscard]] CommandHandle add(const Model &model, const CommandLevel level = Level::Primary)
        { return CommandPool::add(model, level, Lifecycle::Auto); }

    /** @brief Adds a range of commands to the pool
     *  If the number of models is 1 (modelTo - modelFrom), we duplicate the command for each output commands (commandTo - commandFrom) */
    template<CommandModel Model>
    void add(const Model * const modelFrom, const Model * const modelTo,
            CommandHandle * const commandFrom, CommandHandle * const commandTo,
            const CommandLevel level = Level::Primary)
        { CommandPool::add(modelFrom, modelTo, commandFrom, commandTo, level, Lifecycle::Auto); }

    /** @brief Clear every commands at once */
    using CommandPool::clear;

private:
    using CommandPool::add;
    using CommandPool::remove;
};

static_assert_fit_half_cacheline(kF::Graphics::AutoCommandPool);

/** @brief A command pool that let user manager lifecycle of its commands manually */
class kF::Graphics::ManualCommandPool : public CommandPool
{
public:
    /** @brief Construct the command pool */
    ManualCommandPool(Renderer &renderer, const QueueType queueType) : CommandPool(renderer, queueType, Lifecycle::Manual) {}

    /** @brief Move constructor */
    ManualCommandPool(ManualCommandPool &&other) noexcept = default;

    /** @brief Destruct the command pool */
    ~ManualCommandPool(void) = default;

    /** @brief Move assignment */
    ManualCommandPool &operator=(ManualCommandPool &&other) noexcept = default;


    /** @brief Adds a command to the pool */
    template<CommandModel Model>
    [[nodiscard]] CommandHandle add(const Model &model, const CommandLevel level = Level::Primary)
        { return CommandPool::add(model, level, Lifecycle::Manual); }

    /** @brief Adds a range of commands to the pool
     *  If the number of models is 1 (modelTo - modelFrom), we duplicate the command for each output commands (commandTo - commandFrom) */
    template<CommandModel Model>
    void add(const Model * const modelFrom, const Model * const modelTo,
            CommandHandle * const commandFrom, CommandHandle * const commandTo, const CommandLevel level = Level::Primary)
        { CommandPool::add(modelFrom, modelTo, commandFrom, commandTo, level, Lifecycle::Manual); }

    /** @brief Remove a command from the pool */
    using CommandPool::remove;

    /** @brief Clear every commands at once */
    using CommandPool::clear;

private:
    using CommandPool::add;
};

static_assert_fit_half_cacheline(kF::Graphics::ManualCommandPool);

#include "CommandPool.ipp"