/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: CommandPool
 */

template<kF::Graphics::RecorderRequirements Recorder>
inline kF::Graphics::CommandHandle kF::Graphics::CommandPool::add(const Lifecycle lifecycle, const CommandLevel level, Recorder &&recorder)
{
    CommandHandle command;

    add(lifecycle, level, &command, &command + 1, std::forward<Recorder>(recorder));
    return command;
}

template<typename ...Recorders> requires (... && kF::Graphics::RecorderRequirements<Recorders>)
inline void kF::Graphics::CommandPool::add(const Lifecycle lifecycle, const CommandLevel level,
        CommandHandle * const commandFrom, CommandHandle * const commandTo,
        Recorders &&...recorders)
{
    constexpr auto GetCommandUsageFlags = [](const Lifecycle lifecycle) {
        switch (lifecycle) {
        case Lifecycle::Manual:
            return CommandBufferUsageFlags::None;
        case Lifecycle::Auto:
            return CommandBufferUsageFlags::OneTimeSubmit;
        default:
            return CommandBufferUsageFlags::None;
        }
    };

    constexpr auto Begin = [](const CommandHandle command, const VkCommandBufferBeginInfo &commandBeginInfo) {
        if (const auto res = ::vkBeginCommandBuffer(command, &commandBeginInfo); res != VK_SUCCESS)
            throw std::runtime_error("Graphics::CommandPool::add: Couldn't begin command buffer '" + std::string(ErrorMessage(res)) + '\'');
    };

    constexpr auto End = [](const CommandHandle command) {
        if (const auto res = ::vkEndCommandBuffer(command); res != VK_SUCCESS)
            throw std::runtime_error("Graphics::CommandPool::add: Couldn't begin command buffer '" + std::string(ErrorMessage(res)) + '\'');
    };

    kFAssert(sizeof...(Recorders) == std::distance(commandFrom, commandTo),
        throw std::logic_error("Grahpics::CommandPool::add: Mismatching recorder and command count"));

    allocateCommands(level, commandFrom, commandTo);

    const VkCommandBufferBeginInfo commandBeginInfo {
        sType: VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        pNext: nullptr,
        flags: ToFlags(GetCommandUsageFlags(lifecycle)),
        pInheritanceInfo: nullptr
    };

    auto commandIt = commandFrom;
    // Unroll every recorder to record their respective command buffers
    (... , (Begin(*commandIt, commandBeginInfo), recorders(*commandIt), End(*(commandIt++))));
}