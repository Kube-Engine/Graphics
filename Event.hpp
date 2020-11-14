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

/** @brief Abstraction of an event */
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


    /** @brief Set the state of the event to signaled  */
    void signal(void);

    /** @brief Return current event state (signaled / unsignaled) */
    bool isSignaled(void) const;

    /** @brief Set the state of the event to unsignaled */
    void reset(void);

private:

    /** @brief Create the event */
    void createEvent(void);
};