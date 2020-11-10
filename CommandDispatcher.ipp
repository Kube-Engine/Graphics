/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: CommandDispatcher
 */

inline void kF::Graphics::CommandDispatcher::swap(CommandDispatcher &other) noexcept
{
    RendererObject::swap(other);
    _cachedFrames.swap(other);
}

inline void kF::Graphics::CommandDispatcher::prepare(const QueueType queueType, const CommandHandle * const from, const CommandHandle * const to) noexcept
{
    auto &commands = _cachedFrames.currentCache().array[static_cast<std::size_t>(queueType)];

    commands.insert(commands.end(), from, to);
}

inline void kF::Graphics::CommandDispatcher::acquireNextFrame(void) noexcept_ndebug
{
    _cachedFrames.incrementFrame();
    kFAssert(_cachesFrames.cacheAt(_cachedFrames.currentFrame()).cleared,
        throw std::logic_error("Graphics::CommandDispatcher::acquireNextFrame: The frame acquired was not yiet released"));
}

inline void kF::Graphics::CommandDispatcher::releaseFrame([[maybe_unused]] const FrameIndex frameIndex) noexcept
{
#if KUBE_DEBUG_BUILD
    auto &cache = _cachedFrames.cacheAt(frameIndex);
    cache.cleared = true;
    for (auto &commands : cache.array) {
        if (!commands.empty())
            throw std::logic_error("Graphics::CommandDispatcher::releaseFrame: The current frame has still undispatched commands");
    }
#endif
}

inline void kF::Graphics::CommandDispatcher::clear(void) noexcept
{
    for (auto &cache : _cachedFrames.caches()) {
#if KUBE_DEBUG_BUILD
        cache.cleared = true;
#endif
        for (auto &commands : cache)
            commands.clear();
    }
}