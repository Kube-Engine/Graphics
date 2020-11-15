/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: CommandPool
 */

#pragma once

#include "VulkanHandle.hpp"
#include "CommandRecorder.hpp"

namespace kF::Graphics
{
    class CommandPool;
    class ManualCommandPool;
    class AutoCommandPool;

    template<typename Recorder>
    concept RecorderRequirements = requires {
        std::declval<Recorder>().operator()(std::declval<CommandRecorder &>());
    };
}

/** @brief Command pool that allocates command buffers */
class alignas_half_cacheline kF::Graphics::CommandPool : public CachedVulkanHandle<VkCommandPool>
{
public:
    /** @brief Lifecycle of commands inside the pool */
    enum class Lifecycle {
        Manual,
        Auto
    };


    /** @brief Construct the command pool */
    CommandPool(const QueueType queueType, const Lifecycle lifecycle);

    /** @brief Move constructor */
    CommandPool(CommandPool &&other) noexcept = default;

    /** @brief Destruct the command pool */
    ~CommandPool(void) noexcept;

    /** @brief Move assignment */
    CommandPool &operator=(CommandPool &&other) noexcept = default;


    /** @brief Adds a command to the pool */
    template<RecorderRequirements Recorder>
    [[nodiscard]] CommandHandle add(const Lifecycle lifecycle, const CommandLevel level, Recorder &&recorder);

    /** @brief Adds a range of commands to the pool */
    template<typename ...Recorders> requires (... && RecorderRequirements<Recorders>)
    void add(const Lifecycle lifecycle, const CommandLevel level,
            CommandHandle * const commandFrom, CommandHandle * const commandTo,
            Recorders &&...recorders);

    /** @brief Remove a command from the pool */
    void remove(const CommandHandle command) noexcept { remove(&command, &command + 1); }

    /** @brief Remove a range commands from the pool */
    void remove(const CommandHandle * const commandBegin, const CommandHandle * const commandEnd) noexcept;

    /** @brief Clear every commands at once */
    void clear(void) noexcept;


    /** @brief Get the queue level used by the pool */
    [[nodiscard]] QueueType queueType(void) const noexcept { return _queueType; }

private:
    QueueType _queueType { QueueType::Graphics };

    /** @brief Create a command pool */
    void createCommandPool(const QueueType queueType, const Lifecycle lifecycle);

    /** @brief Allocate multiple command buffers */
    void allocateCommands(const CommandLevel level, CommandHandle * const commandFrom, CommandHandle * const commandTo);
};

static_assert_fit_half_cacheline(kF::Graphics::CommandPool);

/** @brief A command pool that can only create one time submit commands */
class kF::Graphics::AutoCommandPool : public CommandPool
{
public:
    /** @brief Construct the command pool */
    AutoCommandPool(const QueueType queueType) : CommandPool(queueType, Lifecycle::Auto) {}

    /** @brief Move constructor */
    AutoCommandPool(AutoCommandPool &&other) noexcept = default;

    /** @brief Destruct the command pool */
    ~AutoCommandPool(void) noexcept = default;

    /** @brief Move assignment */
    AutoCommandPool &operator=(AutoCommandPool &&other) noexcept = default;


    /** @brief Add a one time submit command */
    template<RecorderRequirements Recorder>
    [[nodiscard]] CommandHandle add(const CommandLevel level, Recorder &&recorder)
        { return CommandPool::add(Lifecycle::Auto, level, std::forward<Recorder>(recorder)); }

    /** @brief Adds a range of one time submit commands to the pool */
    template<typename ...Recorders> requires (... && RecorderRequirements<Recorders>)
    void add(const CommandLevel level, CommandHandle * const commandFrom, CommandHandle * const commandTo, Recorders &&...recorders)
        { CommandPool::add(Lifecycle::Auto, level, commandFrom, commandTo, std::forward<Recorders>(recorders)...); }

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
    ManualCommandPool(const QueueType queueType) : CommandPool(queueType, Lifecycle::Manual) {}

    /** @brief Move constructor */
    ManualCommandPool(ManualCommandPool &&other) noexcept = default;

    /** @brief Destruct the command pool */
    ~ManualCommandPool(void) noexcept = default;

    /** @brief Move assignment */
    ManualCommandPool &operator=(ManualCommandPool &&other) noexcept = default;


    /** @brief Add a removable command */
    template<RecorderRequirements Recorder>
    [[nodiscard]] CommandHandle add(const CommandLevel level, Recorder &&recorder)
        { return CommandPool::add(Lifecycle::Manual, level, std::forward<Recorder>(recorder)); }

    /** @brief Adds a range of removable commands to the pool */
    template<typename ...Recorders> requires (... && RecorderRequirements<Recorders>)
    void add(const CommandLevel level, CommandHandle * const commandFrom, CommandHandle * const commandTo, Recorders &&...recorders)
        { CommandPool::add(Lifecycle::Manual, level, commandFrom, commandTo, std::forward<Recorders>(recorders)...); }

    /** @brief Remove a command from the pool */
    using CommandPool::remove;

    /** @brief Clear every commands at once */
    using CommandPool::clear;

private:
    using CommandPool::add;
};

static_assert_fit_half_cacheline(kF::Graphics::ManualCommandPool);

#include "CommandPool.ipp"