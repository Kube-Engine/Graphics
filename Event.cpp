/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Event
 */

#include "Renderer.hpp"
#include "Event.hpp"

using namespace kF;

static void Graphics::Event::Wait(CommandHandle commandBuffer, const EventHandle * const begin, const EventHandle * const end)
{
    ::vkCmdWaitEvents(commandBuffer, std::distance(begin, end), begin, /* ... */);
}

static void Graphics::Event::Reset(void)
{
    if (auto res = ::vkResetEvent(parent().logicalDevice(), handle()); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::Event::Reset: Couldn't reset event '"s + ErrorMessage(res) + '\'');
}

Graphics::Event::~Event(void) noexcept
{
    ::vkDestroyEvent(parent().logicalDevice(), handle(), nullptr);
}

void Graphics::Event::set(void)
{
    if (auto res = ::vkSetEvent(parent().logicalDevice(), handle()); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::Event::set: Couldn't set event status '"s + ErrorMessage(res) + '\'');
}

bool Graphics::Event::isSignaled(void)
{
    const auto res = ::VkGetEventStatus(parent().logicalDevice(), handle());

    if (res == VK_ERROR_OUT_OF_HOST_MEMORY || res == VK_ERROR_OUT_OF_DEVICE_MEMORY || res == VK_ERROR_DEVICE_LOST)
        throw std::runtime_error("Graphics::Event::isSignaled: Couldn't get event status '"s + ErrorMessage(res) + '\'');
    return res == VK_EVENT_SET ? true : false;
}

void Graphics::Event::createEvent(void)
{
    VkEventCreateInfo eventCreateInfo {
        sType: VK_STRUCTURE_TYPE_EVENT_CREATE_INFO,
        pNext: nullptr,
        flags: 0u // Reserved for futur use by Vulkan
    };

    if (auto res = ::vkCreateEvent(parent().logicalDevice(), &eventCreateInfo, nullptr, &handle()); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::Event::createEvent: Couldn't create event '"s + ErrorMessage(res) + '\'');
}