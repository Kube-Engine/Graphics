/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Event
 */

#include <Kube/Core/StringLiteral.hpp>

#include "Renderer.hpp"
#include "Event.hpp"

using namespace kF;
using namespace kF::Literal;

Graphics::Event::~Event(void) noexcept
{
    ::vkDestroyEvent(parent().logicalDevice(), handle(), nullptr);
}

void Graphics::Event::signal(void)
{
    if (const auto res = ::vkSetEvent(parent().logicalDevice(), handle()); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::Event::set: Couldn't set event status '"s + ErrorMessage(res) + '\'');
}

bool Graphics::Event::isSignaled(void) const
{
    const auto res = ::vkGetEventStatus(parent().logicalDevice(), handle());

    if (res == VK_EVENT_SET)
        return true;
    else if (res == VK_EVENT_RESET)
        return false;
    else
        throw std::runtime_error("Graphics::Event::isSignaled: Couldn't get event status '"s + ErrorMessage(res) + '\'');
}

void Graphics::Event::reset(void)
{
    if (const auto res = ::vkResetEvent(parent().logicalDevice(), handle()); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::Event::reset: Couldn't reset event '"s + ErrorMessage(res) + '\'');
}

void Graphics::Event::createEvent(void)
{
    const VkEventCreateInfo eventCreateInfo {
        sType: VK_STRUCTURE_TYPE_EVENT_CREATE_INFO,
        pNext: nullptr,
        flags: 0u
    };

    if (const auto res = ::vkCreateEvent(parent().logicalDevice(), &eventCreateInfo, nullptr, &handle()); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::Event::createEvent: Couldn't create event '"s + ErrorMessage(res) + '\'');
}