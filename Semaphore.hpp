/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Semaphore
 */

#pragma once

#include <vector>

#include "VulkanHandler.hpp"

namespace kF
{
    class Semaphore;

    using Semaphores = std::vector<Semaphore>;
}

class kF::Semaphore final : public VulkanHandler<VkSemaphore>
{
public:
    Semaphore(Renderer &renderer);
    Semaphore(Semaphore &&other) = default;
    ~Semaphore(void);

    Semaphore &operator=(Semaphore &&other) = default;

private:
    void createSemaphore(void);
};