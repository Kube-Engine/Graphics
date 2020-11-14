/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Event
 */

#pragma once

#include "VulkanHandle.hpp"

namespace kF::Graphics
{
    class Event;
}

class kF::Graphics::Event final : public VulkanHandle<VkEvent>
{
public:
    /** @brief Construct a Event */
    Event(void) { createEvent(); }

    /** @brief Move constructor */
    Event(Event &&other) noexcept = default;

    /** @brief Destruct the Event */
    ~Event(void) noexcept;

    /** @brief Move assignment */
    Event &operator=(Event &&other) noexcept = default;
private:

    void createEvent(void);

};