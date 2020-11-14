/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Event
 */

#include "Event.hpp"

using namespace kF;

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