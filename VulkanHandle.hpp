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
    template<typename Type, typename Base>
    class VulkanHandleBase;

    /** @brief Vulkan handle that inherits from RendererObject */
    template<typename Type>
    struct alignas_eighth_cacheline VulkanHandle : public VulkanHandleBase<Type, RendererObject> {};

    /** @brief Vulkan handle that inherits from CachedRendererObject */
    template<typename Type>
    struct alignas_quarter_cacheline CachedVulkanHandle : public VulkanHandleBase<Type, CachedRendererObject> {};
}

/** @brief Abstraction of a vulkan handler */
template<typename Type, typename Base>
class kF::Graphics::VulkanHandleBase : public Base
{
public:
    /** @brief Default construct the handle */
    VulkanHandleBase(void) noexcept = default;

    /** @brief Move constructor */
    VulkanHandleBase(VulkanHandleBase &&other) noexcept : RendererObject(std::move(other)) { swap(other); }

    /** @brief Default constructor, does not release handler */
    ~VulkanHandleBase(void) noexcept = default;

    /** @brief Move assignment */
    VulkanHandleBase &operator=(VulkanHandleBase &&other) noexcept { swap(other); return *this; }

    /** @brief Swap two instances */
    void swap(VulkanHandleBase &other) noexcept { std::swap(_handle, other._handle); }


    /** @brief Fast handle check operator */
    operator bool(void) const noexcept { return isNull(); }

    /** @brief Check if the handle is null */
    [[nodiscard]] bool isNull(void) const noexcept { return _handle == NullHandle; }


    /** @brief Get the vulkan handle */
    [[nodiscard]] Type &handle(void) noexcept { return _handle; }
    [[nodiscard]] const Type &handle(void) const noexcept { return _handle; }

    /** @brief Implicit convertion to handle */
    [[nodiscard]] operator Type(void) const noexcept { return _handle; }

private:
    Type _handle { NullHandle };
};
