/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: CommandDispatcher
 */

#include <numeric>

#include <Kube/Core/StringLiteral.hpp>

#include "Renderer.hpp"
#include "CommandDispatcher.hpp"

using namespace kF;
using namespace kF::Literal;

Graphics::CommandDispatcher::CommandDispatcher(void) noexcept
    : _cachedFrames(parent().cachedFrameCount())
{
}

void Graphics::CommandDispatcher::dispatch(const QueueType queueType)
{


}

void Graphics::CommandDispatcher::onTick(void)
{
    if (tryAcquireNextFrame())
        parent().onNextFrameAcquired(_cachedFrames.currentFrame());
}

bool Graphics::CommandDispatcher::tryAcquireNextFrame(void)
{
    std::uint32_t currentFrame = _cachedFrames.currentFrame();

    res = ::vkAcquireNextImageKHR(
        parent().logicalDevice(), parent().swapchain(),
        UINT64_MAX,
        _avaibleSemaphores[currentFrame],
        NullHandle,
        &currentFrame
    );
    if (res == VK_ERROR_OUT_OF_DATE_KHR || res == VK_SUBOPTIMAL_KHR)
        return;
    else if (res != VK_SUCCESS)
        throw std::runtime_error("Graphics::Drawer::draw: Couldn't acquire next image '"s + ErrorMessage(res) + '\'');
}

void Graphics::CommandDispatcher::presentFrame(void)
{
    constexpr auto UnrollAccumulate = []<std::size_t ...Indexes>(const SemaphoreCounter * const data) {
        return (... + data[Indexes]);
    };

    constexpr auto Merge = [](const Semaphore * const data, const auto count, SemaphoreCache &cache) {
        for (auto i = static_cast<decltype(count)>(0)); i < count; ++i)
            cache.push(data[i].handle());
    };

    constexpr auto UnrollMerge = []<std::size_t ...Indexes>(const SemaphorePool * const pools,
            const SemaphoreCounter * const counters, SemaphoreCache &cache) {
        (... , Merge(pools[Indexes].data(), counters[Indexes], cache);
    };

    using IndexSequence = std::make_index_sequence<QueueCount>;

    // Collect every semaphore in use for the current frame
    auto &cache = _cachedFrames.currentCache();
    const auto count = UnrollAccumulate<IndexSequence>(cache.semaphoreCounters.data());
    if (!count) [[unlikely]] // We can leave now if there are no semaphore in use
        return;
    _semaphoreCache.resize(count);
    UnrollMerge<IndexSequence>(cache.semaphores.data(), cache.semaphoreCounters.data(), _semaphoreCache);

    if (!_frameFences[_cachedFrames.currentFrame()].wait())
        throw std::runtime_error("Graphics::Drawer::draw: Couldn't wait for image fence");

    // Send presentation command with the collected semaphore count
    const auto currentFrame = _cachedFrames.currentFrame();
    const VkPresentInfoKHR presentInfo {
        sType: VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
        pNext: nullptr,
        waitSemaphoreCount: _semaphoreCache.size(),
        pWaitSemaphores: _semaphoreCache.begin(),
        swapchainCount: 1,
        pSwapchains: &parent().swapchain().handle(),
        pImageIndices: &currentFrame,
        pResults: nullptr,
    };
    auto res = ::vkQueuePresentKHR(parent().queueManager().queue(QueueType::Present), &presentInfo);
    if (res != VK_ERROR_OUT_OF_DATE_KHR && res != VK_SUBOPTIMAL_KHR)
        throw std::runtime_error("Graphics::Drawer::draw: Couldn't setup queue present '"s + ErrorMessage(res) + '\'');
    _semaphoreCache.clear();
}