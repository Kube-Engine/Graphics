/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Fence
 */

#pragma once

#include <vector>

#include "VulkanHandler.hpp"

namespace kF
{
    class Fence;

    using Fences = std::vector<Fence>;
}

class kF::Fence final : public VulkanHandler<VkFence>
{
public:
    Fence(Renderer &renderer);
    Fence(Fence &&other) = default;
    ~Fence(void);

    Fence &operator=(Fence &&other) = default;

    bool waitToBeSignaled(const std::uint64_t timeout = UINT64_MAX) const;

    void resetFence(void);

private:
    void createFence(void);
};