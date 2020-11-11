/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Semaphore
 */

#pragma once

#include <vector>

#include "VulkanHandle.hpp"

namespace kF::Graphics
{
    class Semaphore;

    /** @brief A list of semaphores */
    using Semaphores = std::vector<Semaphore>;
}

/** @brief Abstraction of a low-level system semaphore */
class kF::Graphics::Semaphore final : public VulkanHandle<VkSemaphore>
{
public:
    /** @brief Construct a semaphore */
    Semaphore(Renderer &renderer) : VulkanHandle<VkSemaphore>(renderer)
        { createSemaphore(); }

    /** @brief Move constructor */
    Semaphore(Semaphore &&other) noexcept = default;

    /** @brief Destruct the semaphore */
    ~Semaphore(void) noexcept;

    /** @brief Move constructor */
    Semaphore &operator=(Semaphore &&other) noexcept = default;

private:
    void createSemaphore(void);
};