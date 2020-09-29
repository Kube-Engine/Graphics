/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: CommandPool
 */

#include <vector>
#include <memory>

#include "LogicalDevice.hpp"
#include "QueueHandler.hpp"
#include "FramebufferHandler.hpp"
#include "RenderModel.hpp"

namespace kF
{
    class CommandPool;
    struct CommandModel;

    using Command = VkCommandBuffer;
    using Commands = std::vector<Command>;
    using CommandIndex = std::uint32_t;
    using CommandIndexes = std::vector<CommandIndex>;
}

struct kF::CommandModel
{
    PipelineIndex pipeline;
    RenderModel renderModel;
};

class kF::CommandPool final : public VulkanHandler<VkCommandPool>
{
public:
    using CommandPair = std::pair<CommandIndex, std::unique_ptr<Commands>>;
    using CommandMap = std::vector<CommandPair>;
    using CommandModelMap = std::vector<std::unique_ptr<CommandModel>>;

    CommandPool(Renderer &renderer);
    CommandPool(CommandPool &&other) = default;
    ~CommandPool(void);

    CommandPool &operator=(CommandPool &&other) = default;

    [[nodiscard]] CommandIndex addCommand(const CommandModel &model);
    void removeCommand(const CommandIndex index);

    [[nodiscard]] Commands &getCommands(const CommandIndex index);
    [[nodiscard]] const Commands &getCommands(const CommandIndex index) const;

    void onViewSizeChanged(void);

private:
    CommandMap _commandMap {};
    CommandModelMap _modelMap {};

#ifndef KUBE_NO_DYNAMIC_RESIZE
    VkViewport _viewport {};
    VkRect2D _scissor {};
#endif

    void createCommandPool(void);
    void allocateCommands(const CommandModel &model, Commands &commands);
    void recordCommands(const CommandModel &model, Commands &commands);
    void destroyCommands(Commands &commands) noexcept;

    auto findCommand(const CommandIndex index) noexcept { return std::find_if(_commandMap.begin(), _commandMap.end(), [index](const auto &pair) { return pair.first == index; }); }
    auto findCommand(const CommandIndex index) const noexcept { return std::find_if(_commandMap.begin(), _commandMap.end(), [index](const auto &pair) { return pair.first == index; }); }
};