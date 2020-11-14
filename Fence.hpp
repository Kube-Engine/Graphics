/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Fence
 */

#pragma once

#include <vector>

#include "VulkanHandle.hpp"

namespace kF::Graphics
{
    class Fence;
}

/** @brief Abstraction of a low level system fence */
class kF::Graphics::Fence final : public VulkanHandle<VkFence>
{
public:
    /** @brief Wait fences to be signaled */
    static bool Wait(const FenceHandle * const begin, const FenceHandle * const end, const bool waitAll = true, const std::uint64_t timeout = UINT64_MAX);

    /** @brief Reset fences to be signaled */
    static void Reset(const FenceHandle * const begin, const FenceHandle * const end) noexcept;


    /** @brief Construct the fence */
    Fence(void) { createFence(); }

    /** @brief Move constructor */
    Fence(Fence &&other) noexcept = default;

    /** @brief Destroy the fence */
    ~Fence(void) noexcept;

    /** @brief Move assignment */
    Fence &operator=(Fence &&other) noexcept = default;


    /** @brief Wait the fence to be signaled */
    bool wait(const std::uint64_t timeout = UINT64_MAX) const
        { return Wait(&handle(), &handle() + 1, true, timeout); }

    /** @brief Reset the fence */
    void reset(void) noexcept
        { Reset(&handle(), &handle() + 1); }

private:
    /** @brief Create the fence */
    void createFence(void);
};