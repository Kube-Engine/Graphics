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
    //** @brief Wait for one or more events to enter the signaled state */
    static void Wait(CommandHandle commandBuffer, const EventHandle * const begin, const EventHandle * const end);

    /** @brief Set the state of the event to unsignaled */
    static void Reset(void);


    /** @brief Construct a Event */
    Event(void) { createEvent(); }

    /** @brief Move constructor */
    Event(Event &&other) noexcept = default;

    /** @brief Destruct the Event */
    ~Event(void) noexcept;

    /** @brief Move assignment */
    Event &operator=(Event &&other) noexcept = default;


    /** @brief Set the state of the event to signaled  */
    void set(void);

    /** @brief Return current event state (signaled / unsignaled) */
    bool isSignaled(void);


    /** @brief Wait for one or more events to enter the signaled state */
    void wait(CommandHandle commandBuffer);
        { Wait(commandBuffer, &handle(), &handle() + 1); }

    /** @brief Set the state of the event to unsignaled */
    void reset(void)
        { Reset(); }

private:

    /** @brief Create the event */
    void createEvent(void);
};