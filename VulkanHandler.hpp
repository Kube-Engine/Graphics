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
    class VulkanHandler;
}

/** @brief Abstraction of a vulkan handler */
template<typename Type>
class kF::Graphics::VulkanHandler : public RendererObject
{
public:
    /** @brief Default construct the handle */
    VulkanHandler(Renderer &renderer) : RendererObject(renderer) {}

    /** @brief Move constructor */
    VulkanHandler(VulkanHandler<Type> &&other) noexcept : RendererObject(std::move(other)) { swap(other); }

    /** @brief Default constructor, does not release handler */
    ~VulkanHandler(void) noexcept = default;

    /** @brief Move assignment */
    VulkanHandler<Type> &operator=(VulkanHandler<Type> &&other) noexcept { swap(other); return *this; }

    /** @brief Implicit convertion to handle */
    [[nodiscard]] operator const Type(void) const noexcept { return _handle; }

    /** @brief Check if the handle is null */
    [[nodiscard]] bool isNull(void) const noexcept { return _handle == VK_NULL_HANDLE; }

    /** @brief Get the vulkan handle */
    [[nodiscard]] Type &handle(void) noexcept { return _handle; }
    [[nodiscard]] const Type &handle(void) const noexcept { return _handle; }

    /** @brief Swap two instances */
    void swap(VulkanHandler<Type> &other) noexcept { std::swap(_handle, other._handle); }

private:
    Type _handle = VK_NULL_HANDLE;
};