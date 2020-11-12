/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Drawer
 */

#include <algorithm>
#include <iostream>

#include <Kube/Core/StringLiteral.hpp>

#include "Renderer.hpp"

using namespace kF;
using namespace kF::Literal;

Graphics::Drawer::Drawer(Renderer &renderer, const std::uint32_t asyncFrameCount) : RendererObject(renderer),
    _asyncFrameCount(asyncFrameCount)
{
    _avaibleSemaphores.reserve(_asyncFrameCount);
    _finishedSemaphores.reserve(_asyncFrameCount);
    _frameFences.reserve(_asyncFrameCount);
    for (auto i = 0u; i < asyncFrameCount; ++i) {
        _avaibleSemaphores.emplace_back(parent());
        _finishedSemaphores.emplace_back(parent());
        _frameFences.emplace_back(parent());
    }
}

Graphics::Drawer::~Drawer(void)
{
    waitAllDrawCompleted();
}

void Graphics::Drawer::addCommandIndex(const CommandIndex command)
{
    _commandIndexes.emplace_back(command);
    _commands.resize(_commandIndexes.size());
}

void Graphics::Drawer::removeCommandIndex(const CommandIndex command)
{
    auto it = std::find(_commandIndexes.begin(), _commandIndexes.end(), command);

    if (it == _commandIndexes.end())
        throw std::runtime_error("Graphics::Drawer::removeCommandIndex: Couldn't find index '" + std::to_string(command) + '\'');
    _commandIndexes.erase(it);
    _commands.resize(_commandIndexes.size());
}

void Graphics::Drawer::clearCommandIndexes(void) noexcept
{
    _commandIndexes.clear();
    _commands.clear();
}

void Graphics::Drawer::draw(void)
{
    VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    VkSubmitInfo submitInfo {
        sType: VK_STRUCTURE_TYPE_SUBMIT_INFO,
        pNext: nullptr,
        waitSemaphoreCount: 1,
        pWaitSemaphores: &_avaibleSemaphores[_currentFrame].handle(),
        pWaitDstStageMask: waitStages,
        commandBufferCount: static_cast<std::uint32_t>(_commands.size()),
        pCommandBuffers: _commands.data(),
        signalSemaphoreCount: 1,
        pSignalSemaphores: &_finishedSemaphores[_currentFrame].handle()
    };
    std::uint32_t imageIndex;
    VkResult res;

    if (!_frameFences[_currentFrame].wait())
        throw std::runtime_error("Graphics::Drawer::draw: Couldn't wait for image fence");
    res = ::vkAcquireNextImageKHR(
        parent().logicalDevice(), parent().swapchain(),
        UINT64_MAX,
        _avaibleSemaphores[_currentFrame],
        NullHandle,
        &imageIndex
    );
    if (res == VK_ERROR_OUT_OF_DATE_KHR || res == VK_SUBOPTIMAL_KHR)
        return;
    else if (res != VK_SUCCESS)
        throw std::runtime_error("Graphics::Drawer::draw: Couldn't acquire next image '"s + ErrorMessage(res) + '\'');
    retreiveFrameCommands(imageIndex);
    _frameFences[_currentFrame].reset();
    res = ::vkQueueSubmit(parent().queueManager().queue(QueueType::Graphics), 1, &submitInfo, _frameFences[_currentFrame]);
    if (res != VK_SUCCESS)
        throw std::runtime_error("Graphics::Drawer::draw: Couldn't submit queue '"s + ErrorMessage(res) + '\'');
    presentImage(imageIndex);
    _currentFrame = (_currentFrame + 1) % _asyncFrameCount;
}

void Graphics::Drawer::retreiveFrameCommands(const std::uint32_t imageIndex) noexcept
{
    for (auto i = 0u; i < _commands.size(); ++i)
        _commands[i] = parent().commandPool().getCommands(_commandIndexes[i])[imageIndex];
}

void Graphics::Drawer::presentImage(const std::uint32_t imageIndex)
{
    VkPresentInfoKHR presentInfo {
        sType: VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
        pNext: nullptr,
        waitSemaphoreCount: 1,
        pWaitSemaphores: &_finishedSemaphores[_currentFrame].handle(),
        swapchainCount: 1,
        pSwapchains: &parent().swapchain().handle(),
        pImageIndices: &imageIndex,
        pResults: nullptr,
    };
    auto res = ::vkQueuePresentKHR(parent().queueManager().queue(QueueType::Present), &presentInfo);

    if (res == VK_ERROR_OUT_OF_DATE_KHR || res == VK_SUBOPTIMAL_KHR)
        return;
    else if (res != VK_SUCCESS)
        throw std::runtime_error("Graphics::Drawer::draw: Couldn't setup queue present '"s + ErrorMessage(res) + '\'');
}

void Graphics::Drawer::waitAllDrawCompleted(void)
{
    for (auto &fence : _frameFences)
        fence.wait();
    ::vkDeviceWaitIdle(parent().logicalDevice());
}