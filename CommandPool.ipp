/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: CommandPool
 */

template<kF::Graphics::CommandModel Model>
inline kF::Graphics::CommandHandle kF::Graphics::CommandPool::add(const Model &model, const Level level, const Lifecycle lifecycle)
{
    Command command;

    add(&model, &model + 1, &command, &command + 1, level, lifecycle);
    return command;
}

template<kF::Graphics::CommandModel Model>
inline void kF::Graphics::CommandPool::add(const Model * const modelFrom, const Model * const modelTo,
        Command * const commandFrom, Command * const commandTo, const Level level, const Lifecycle lifecycle)
{
    kFAssert(std::distance(modelFrom, modelTo) == std::distance(commandFrom, commandTo),
        throw std::logic_error("Grahpics::CommandPool::add: Mismatching model and command count"));

    VkCommandBufferBeginInfo commandBeginInfo {
        sType: VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        pNext: nullptr,
        flags: GetCommandUsageFlags(lifecycle),
        pInheritanceInfo: nullptr
    };

    allocateCommands(commandFrom, commandTo, level);
    if constexpr (std::is_same_v<Model, RenderModel>)
        recordRender(modelFrom, modelTo, commandFrom, commandTo, commandBeginInfo);
    else
        recordTransfer(modelFrom, modelTo, commandFrom, commandTo, commandBeginInfo);
}

inline VkCommandBufferUsageFlags kF::Graphics::CommandPool::GetCommandUsageFlags(const Lifecycle lifecycle)
{
    switch (lifecycle) {
    case Lifecycle::Manual:
        return VkCommandBufferUsageFlags();
    case Lifecycle::Auto:
        return VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    }
}