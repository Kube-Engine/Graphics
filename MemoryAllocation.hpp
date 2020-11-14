/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: MemoryAllocation
 */

#pragma once

#include "MemoryAllocationModel.hpp"
#include "VulkanHandle.hpp"

namespace kF::Graphics
{
    class MemoryAllocation;
}

/** @brief GPU Memory buffer abstraction */
class kF::Graphics::MemoryAllocation final : public VulkanHandle<MemoryAllocationHandle>
{
public:
    /** @brief Construct a nw buffer using a buffer model */
    MemoryAllocation(const MemoryAllocationModel &model) { createMemoryAllocation(model); }

    /** @brief Move constructor */
    MemoryAllocation(MemoryAllocation &&other) noexcept = default;

    /** @brief Destruct the buffer */
    ~MemoryAllocation(void) noexcept;

    /** @brief Move assignment */
    MemoryAllocation &operator=(MemoryAllocation &&other) noexcept = default;

private:
    /** @brief Create the device buffer */
    void createMemoryAllocation(const MemoryAllocationModel &model);
};