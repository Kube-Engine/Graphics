/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Vulkan Handler helper
 */

#pragma once

#include <utility>

#include "Vulkan.hpp"
#include "RendererObject.hpp"

namespace kF::Graphics
{
    template<typename Type>
    class VulkanHandle;
}

/** @brief Abstraction of a vulkan handler */
template<typename Type>
class alignas_quarter_cacheline kF::Graphics::VulkanHandle : public RendererObject
{
public:
    /** @brief Default construct the handle */
    VulkanHandle(Renderer &renderer) : RendererObject(renderer) {}

    /** @brief Move constructor */
    VulkanHandle(VulkanHandle &&other) noexcept : RendererObject(std::move(other)) { swap(other); }

    /** @brief Default constructor, does not release handler */
    ~VulkanHandle(void) noexcept = default;

    /** @brief Move assignment */
    VulkanHandle &operator=(VulkanHandle &&other) noexcept { swap(other); return *this; }

    /** @brief Implicit convertion to handle */
    [[nodiscard]] operator const Type(void) const noexcept { return _handle; }

    /** @brief Fast handle check operator */
    operator bool(void) const noexcept { return isNull(); }

    /** @brief Check if the handle is null */
    [[nodiscard]] bool isNull(void) const noexcept { return _handle == NullHandle; }

    /** @brief Get the vulkan handle */
    [[nodiscard]] Type &handle(void) noexcept { return _handle; }
    [[nodiscard]] const Type &handle(void) const noexcept { return _handle; }

    /** @brief Swap two instances */
    void swap(VulkanHandle &other) noexcept { RendererObject::swap(other); std::swap(_handle, other._handle); }

private:
    Type _handle = NullHandle;
};
