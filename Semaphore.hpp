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
}

/** @brief Abstraction of a low-level system semaphore */
class kF::Graphics::Semaphore final : public VulkanHandle<SemaphoreHandle>
{
public:
    /** @brief Construct a semaphore */
    Semaphore(void) { createSemaphore(); }

    /** @brief Move constructor */
    Semaphore(Semaphore &&other) noexcept = default;

    /** @brief Destruct the semaphore */
    ~Semaphore(void) noexcept;

    /** @brief Move constructor */
    Semaphore &operator=(Semaphore &&other) noexcept = default;

private:
    void createSemaphore(void);
};