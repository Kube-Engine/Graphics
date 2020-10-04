/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: CommandPool
 */

#pragma once

#include <vector>
#include <memory>

#include "LogicalDevice.hpp"
#include "QueueHandler.hpp"
#include "FramebufferHandler.hpp"
#include "RenderModel.hpp"

namespace kF::Graphics
{
    class CommandPool;
    struct CommandModel;

    using Command = VkCommandBuffer;
    using Commands = std::vector<Command>;
    using CommandIndex = std::uint32_t;
    using CommandIndexes = std::vector<CommandIndex>;
}

/** @brief Describe a command to be constructed */
struct kF::Graphics::CommandModel
{
    PipelineIndex pipeline;
    RenderModel renderModel;
};

/** @brief Abstract a low level pool of command buffers, not thread safe */
class kF::Graphics::CommandPool final : public VulkanHandler<VkCommandPool>
{
public:
    using CommandPair = std::pair<CommandIndex, std::unique_ptr<Commands>>;
    using CommandMap = std::vector<CommandPair>;
    using CommandModelMap = std::vector<std::unique_ptr<CommandModel>>;

    /** @brief Construct a command pool */
    CommandPool(Renderer &renderer);

    /** @brief Move constructor */
    CommandPool(CommandPool &&other) noexcept = default;

    /** @brief Destruct the command pool */
    ~CommandPool(void) noexcept;

    /** @brief Move assignment */
    CommandPool &operator=(CommandPool &&other) noexcept = default;

    /** @brief Add a command to the pool
     *  @return Index of the command */
    [[nodiscard]] CommandIndex addCommand(const CommandModel &model);

    /** @brief Remove a command from the pool using its index */
    void removeCommand(const CommandIndex index);

    /** @brief Get the command vector */
    [[nodiscard]] Commands &getCommands(const CommandIndex index);
    [[nodiscard]] const Commands &getCommands(const CommandIndex index) const;

    /** @brief Callback on render view size changed */
    void onViewSizeChanged(void);

private:
    CommandMap _commandMap {};
    CommandModelMap _modelMap {};

#ifndef KUBE_NO_DYNAMIC_RESIZE
    VkViewport _viewport {};
    VkRect2D _scissor {};
#endif

    /** @brief Create the command pool */
    void createCommandPool(void);

    /** @brief Allocate a set of commands in the pool */
    void allocateCommands(const CommandModel &model, Commands &commands);

    /** @brief Record a set of commands in the pool */
    void recordCommands(const CommandModel &model, Commands &commands);

    /** @brief Destroy a set of commands in the pool */
    void destroyCommands(Commands &commands) noexcept;

    /** @brief Find a command in the pool using its index */
    auto findCommand(const CommandIndex index) noexcept { return std::find_if(_commandMap.begin(), _commandMap.end(), [index](const auto &pair) { return pair.first == index; }); }
    auto findCommand(const CommandIndex index) const noexcept { return std::find_if(_commandMap.begin(), _commandMap.end(), [index](const auto &pair) { return pair.first == index; }); }
};