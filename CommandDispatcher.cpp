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

void Graphics::CommandDispatcher::dispatch(const QueueType queueType,
        const SubmitInfo * const submitBegin, const SubmitInfo * const submitEnd, const FenceHandle fence)
{
    const auto res = ::vkQueueSubmit(
        parent().queueManager().queue(queueType),
        static_cast<std::uint32_t>(std::distance(submitBegin, submitEnd)),
        submitBegin,
        fence
    );
    if (res != VK_SUCCESS)
        throw std::runtime_error("Graphics::Drawer::draw: Couldn't submit to queue '"s + ErrorMessage(res) + '\'');
}

bool Graphics::CommandDispatcher::tryAcquireNextFrame(void)
{
    constexpr auto UnrollClear = []<std::size_t ...Indexes>(SemaphoreCache * const data, std::index_sequence<Indexes...>) {
        (... , data[Indexes].clear());
    };

    // Retreive a free semaphore for the next frame
    if (_availableSemaphores.empty()) [[unlikely]]
        _availableSemaphores.push();
    Semaphore semaphore { std::move(_availableSemaphores.back()) };
    _availableSemaphores.pop();

    // Try to retreive the next frame handle
    std::uint32_t retreivedFrame;
    const auto res = ::vkAcquireNextImageKHR(
        parent().logicalDevice(),
        parent().swapchain(),
        UINT64_MAX, // No timeout
        semaphore,
        NullHandle, // No fence
        &retreivedFrame
    );
    if (res != VK_SUCCESS) { // Check if the frame has been acquired or not
        _availableSemaphores.push(std::move(semaphore)); // If not, store the free semaphore for later use
        if (res == VK_TIMEOUT || res == VK_ERROR_OUT_OF_DATE_KHR || res == VK_SUBOPTIMAL_KHR)
            return false;
        else
            throw std::runtime_error("Graphics::Drawer::draw: Couldn't acquire next image '"s + ErrorMessage(res) + '\'');
    }

    // Update the new current frame and its 'available' semaphore then clear old frame data
    _cachedFrames.setCurrentFrame(retreivedFrame);
    auto &cache = _cachedFrames.currentCache();
    auto &cachedSemaphore = cache.frameAvailable;
    if (cachedSemaphore.has_value()) [[likely]]
        _availableSemaphores.push(std::move(cachedSemaphore.value()));
    cachedSemaphore.emplace(std::move(semaphore));
    UnrollClear(cache.perQueueSemaphoreCache.data(), PerQueueIndexSequence);
    cache.semaphoreCache.clear();
    parent().dispatchFrameAcquired(retreivedFrame);
    return true;
}

void Graphics::CommandDispatcher::presentFrame(void)
{
    constexpr auto UnrollAccumulate = []<std::size_t ...Indexes>(const SemaphoreCache * const data, std::index_sequence<Indexes...>) -> std::size_t {
        return (... + data[Indexes].size());
    };

    constexpr auto UnrollMerge = []<std::size_t ...Indexes>(const SemaphoreCache * const data, SemaphoreCache &to, std::index_sequence<Indexes...>) -> void {
        (... , to.insert(to.end(), data[Indexes].begin(), data[Indexes].end()));
    };

    // Collect every semaphore in use for the current frame
    auto &cache = _cachedFrames.currentCache();
    const auto count = UnrollAccumulate(cache.perQueueSemaphoreCache.data(), PerQueueIndexSequence);
    if (count) [[likely]] {
        cache.semaphoreCache.resize(count);
        UnrollMerge(cache.perQueueSemaphoreCache.data(), cache.semaphoreCache, PerQueueIndexSequence);
    }

    // Send presentation command with the collected semaphore count
    const std::uint32_t currentFrame = _cachedFrames.currentFrame();
    const VkPresentInfoKHR presentInfo {
        sType: VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
        pNext: nullptr,
        waitSemaphoreCount: cache.semaphoreCache.size(),
        pWaitSemaphores: cache.semaphoreCache.begin(),
        swapchainCount: 1,
        pSwapchains: &parent().swapchain().handle(),
        pImageIndices: &currentFrame,
        pResults: nullptr,
    };
    const auto res = ::vkQueuePresentKHR(parent().queueManager().queue(QueueType::Present), &presentInfo);
    if (res != VK_ERROR_OUT_OF_DATE_KHR && res != VK_SUBOPTIMAL_KHR)
        throw std::runtime_error("Graphics::Drawer::draw: Couldn't setup queue present '"s + ErrorMessage(res) + '\'');
    cache.semaphoreCache.clear();
}