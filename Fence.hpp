/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Fence
 */

#pragma once

#include <vector>

#include "VulkanHandler.hpp"

namespace kF::Graphics
{
    class Fence;

    using Fences = std::vector<Fence>;
}

/** @brief Abstraction of a low level system fence */
class kF::Graphics::Fence final : public VulkanHandler<VkFence>
{
public:
    /** @brief Construct the fence */
    Fence(Renderer &renderer);

    /** @brief Move constructor */
    Fence(Fence &&other) noexcept = default;

    /** @brief Destroy the fence */
    ~Fence(void) noexcept;

    /** @brief Move assignment */
    Fence &operator=(Fence &&other) noexcept = default;

    /** @brief Wait the fence to be signaled */
    bool waitToBeSignaled(const std::uint64_t timeout = UINT64_MAX) const;

    /** @brief Reset the fence */
    void resetFence(void) noexcept;

private:
    /** @brief Create the fence */
    void createFence(void);
};