/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Vulkan Handler helper
 */

#pragma once

#include <utility>

#include "Vulkan.hpp"

#include "RendererObject.hpp"

namespace kF
{
    template<typename Type>
    class VulkanHandler;
}

template<typename Type>
class kF::VulkanHandler : public RendererObject
{
public:
    VulkanHandler(Renderer &renderer) : RendererObject(renderer) {}
    VulkanHandler(VulkanHandler<Type> &&other) : RendererObject(std::move(other)) { swap(other); }
    ~VulkanHandler(void) = default;

    VulkanHandler<Type> &operator=(VulkanHandler<Type> &&other) { swap(other); return *this; }

    [[nodiscard]] operator const Type(void) const noexcept { return _handle; }

    [[nodiscard]] bool isNull(void) const noexcept { return _handle == VK_NULL_HANDLE; }

    [[nodiscard]] Type &handle(void) noexcept { return _handle; }
    [[nodiscard]] const Type &handle(void) const noexcept { return _handle; }

    void swap(VulkanHandler<Type> &other) noexcept { std::swap(_handle, other._handle); }

private:
    Type _handle = VK_NULL_HANDLE;
};