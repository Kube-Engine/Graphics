/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Drawer
 */

#include <algorithm>
#include <iostream>

#include <Kube/Core/Core.hpp>

#include "Renderer.hpp"

using namespace kF;
using namespace kF::Literal;

Drawer::Drawer(Renderer &renderer, const std::uint32_t asyncFrameCount) : RendererObject(renderer),
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

Drawer::~Drawer(void)
{
    waitAllDrawCompleted();
}

void Drawer::addCommandIndex(const CommandIndex command)
{
    _commandIndexes.emplace_back(command);
    _commands.resize(_commandIndexes.size());
}

void Drawer::removeCommandIndex(const CommandIndex command)
{
    auto it = std::find(_commandIndexes.begin(), _commandIndexes.end(), command);

    if (it == _commandIndexes.end())
        throw std::runtime_error("Drawer::removeCommandIndex: Couldn't find index '" + std::to_string(command) + '\'');
    _commandIndexes.erase(it);
    _commands.resize(_commandIndexes.size());
}

void Drawer::clearCommandIndexes(void)
{
    _commandIndexes.clear();
    _commands.clear();
}

void Drawer::draw(void)
{
    VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    VkSubmitInfo submitInfo {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .pNext = nullptr,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = &_avaibleSemaphores[_currentFrame].handle(),
        .pWaitDstStageMask = waitStages,
        .commandBufferCount = static_cast<std::uint32_t>(_commands.size()),
        .pCommandBuffers = _commands.data(),
        .signalSemaphoreCount = 1,
        .pSignalSemaphores = &_finishedSemaphores[_currentFrame].handle()
    };
    std::uint32_t imageIndex;
    VkResult res;

    if (!_frameFences[_currentFrame].waitToBeSignaled())
        throw std::runtime_error("Drawer::draw: Couldn't wait for image fence");
    res = ::vkAcquireNextImageKHR(parent().getLogicalDevice(), parent().getSwapchain(), UINT64_MAX, _avaibleSemaphores[_currentFrame], VK_NULL_HANDLE, &imageIndex);
    if (res == VK_ERROR_OUT_OF_DATE_KHR || res == VK_SUBOPTIMAL_KHR)
        return;
    else if (res != VK_SUCCESS)
        throw std::runtime_error("Drawer::draw: Couldn't acquire next image '"_str + ErrorMessage(res) + '\'');
    retreiveFrameCommands(imageIndex);
    _frameFences[_currentFrame].resetFence();
    res = ::vkQueueSubmit(parent().getQueueHandler().getQueue(QueueType::Graphics), 1, &submitInfo, _frameFences[_currentFrame]);
    if (res != VK_SUCCESS)
        throw std::runtime_error("Drawer::draw: Couldn't submit queue '"_str + ErrorMessage(res) + '\'');
    presentImage(imageIndex);
    _currentFrame = (_currentFrame + 1) % _asyncFrameCount;
}

void Drawer::retreiveFrameCommands(const std::uint32_t imageIndex) noexcept
{
    for (auto i = 0; i < _commands.size(); ++i)
        _commands[i] = parent().getCommandPool().getCommands(_commandIndexes[i])[imageIndex];
}

void Drawer::presentImage(const std::uint32_t imageIndex)
{
    VkPresentInfoKHR presentInfo {
        .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
        .pNext = nullptr,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = &_finishedSemaphores[_currentFrame].handle(),
        .swapchainCount = 1,
        .pSwapchains = &parent().getSwapchain().handle(),
        .pImageIndices = &imageIndex,
        .pResults = nullptr,
    };
    auto res = ::vkQueuePresentKHR(parent().getQueueHandler().getQueue(QueueType::Present), &presentInfo);

    if (res == VK_ERROR_OUT_OF_DATE_KHR || res == VK_SUBOPTIMAL_KHR)
        return;
    else if (res != VK_SUCCESS)
        throw std::runtime_error("Drawer::draw: Couldn't setup queue present '"_str + ErrorMessage(res) + '\'');
}

void Drawer::waitAllDrawCompleted(void)
{
    for (auto &fence : _frameFences)
        fence.waitToBeSignaled();
    ::vkDeviceWaitIdle(parent().getLogicalDevice());
}