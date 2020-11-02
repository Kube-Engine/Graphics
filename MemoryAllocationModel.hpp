/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: MemoryAllocationModel
 */

#pragma once

#include <vk_mem_alloc.h>

#include "Buffer.hpp"
#include "Image.hpp"

namespace kF::Graphics
{
    struct MemoryAllocationModel;

    /** @brief All kinds of memory types */
    enum class MemoryUsage : std::uint32_t {
        DeviceOnly = VMA_MEMORY_USAGE_GPU_ONLY,
        HostOnly = VMA_MEMORY_USAGE_CPU_ONLY,
        DeviceToHost = VMA_MEMORY_USAGE_GPU_TO_CPU,
        HostToDevice = VMA_MEMORY_USAGE_CPU_TO_GPU
    };

    /** @brief Type of memory allocated */
    enum class MemoryType : std::uint32_t {
        Buffer = 0u,
        Image
    };
}

class kF::Graphics::MemoryAllocationModel
{
public:
    /** @brief Can either contain a buffer or an image */
    union Data
    {
        DeviceBuffer buffer { VK_NULL_HANDLE };
        DeviceImage image;
    };

    /** @brief Construct a new memory allocation */
    template<typename Type> requires std::same_as<Type, DeviceBuffer> || std::same_as<Type, DeviceImage>
    MemoryAllocationModel(const Type &value, const MemoryUsage usage) noexcept;

    /** @brief Copy constructor */
    MemoryAllocationModel(const MemoryAllocationModel &other) noexcept = default;

    /** @brief Copy assignment */
    MemoryAllocationModel &operator=(const MemoryAllocationModel &other) noexcept = default;


    /** @brief Get the usage of memory */
    [[nodiscard]] MemoryUsage memoryUsage(void) const noexcept { return _usage; }


    /** @brief Get the type of memory */
    [[nodiscard]] MemoryType memoryType(void) const noexcept { return _type; }

    /** @brief Retreive data as a buffer */
    [[nodiscard]] DeviceBuffer buffer(void) const noexcept { return _data.buffer; }

    /** @brief Retreive data as an image */
    [[nodiscard]] DeviceImage image(void) const noexcept { return _data.image; }

private:
    Data _data {};
    MemoryUsage _usage { MemoryUsage::DeviceOnly };
    MemoryType _type { MemoryType::Buffer };
};

#include "MemoryAllocationModel.ipp"