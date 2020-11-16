/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: MemoryAllocation
 */

#pragma once

#include "MemoryAllocationModel.hpp"
#include "VulkanHandle.hpp"
#include "MemoryAllocator.hpp"

namespace kF::Graphics
{
    class MemoryAllocation;
}

/** @brief GPU Memory buffer abstraction */
class kF::Graphics::MemoryAllocation final : public VulkanHandle<MemoryAllocationHandle>
{
public:
    /** @brief Make a memory allocation for a staging buffer and copy its memory */
    template<MemoryBindable Bindable, std::input_iterator Iterator>
    [[nodiscard]] static inline MemoryAllocation MakeStaging(const Bindable toBind, const Iterator dataBegin, const Iterator dataEnd);

    /** @brief Make a local (GPU only) memory allocation and bind a vertex buffer */
    template<MemoryBindable Bindable>
    [[nodiscard]] static inline MemoryAllocation MakeLocal(const Bindable toBind) noexcept
        { return MemoryAllocation(MemoryAllocationModel::MakeLocal(toBind)); }


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

#include "MemoryAllocation.ipp"