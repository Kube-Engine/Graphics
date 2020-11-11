/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Vulkan utils
 */

#pragma once

#include <Kube/Core/Utils.hpp>

#include "VulkanEnums.hpp"

namespace kF::Graphics
{
    /** @brief Null handle alias */
    constexpr auto NullHandle = NullHandle;

    /** @brief 3D extent */
    using Extent3D = VkExtent3D;


    /** @brief Fence handle */
    using FenceHandle = VkFence;

    /** @brief Fence handle */
    using SemaphoreHandle = VkFence;


    /** @brief Render pass handle */
    using RenderPassHandle = VkRenderPass;


    /** @brief A frame buffer handle */
    using FrameBufferHandle = VkFramebuffer;


    /** @brief A vulkan queue */
    using QueueHandle = VkQueue;


    /** @brief Command handle */
    using CommandHandle = VkCommandBuffer;


    /** @brief Device memory allocation */
    using MemoryAllocationHandle = VmaAllocation;


    /** @brief Vulkan buffer */
    using BufferHandle = VkBuffer;

    /** @brief Size of a buffer */
    using BufferSize = VkDeviceSize;

    /** @brief Offset in a buffer */
    using BufferOffset = VkDeviceSize;


    /** @brief Image handle */
    using ImageHandle = VkImageView;

    /** @brief Image view handle */
    using ImageViewHandle = VkImageView;


    /** @brief Get an error message from a vulkan result */
    [[nodiscard]] const char *ErrorMessage(VkResult res);

    /** @brief Fill a container using a vulkan style getter with VkResult as return type */
    template<typename Container, typename ...FunctionArgs, typename ...Args>
    [[nodiscard]] VkResult FillVkContainer(Container &container, VkResult(*function)(FunctionArgs...), Args &&...args)
    {
        std::uint32_t count = 0;
        VkResult res = (*function)(std::forward<Args>(args)..., &count, nullptr);
        if (res != VK_SUCCESS || !count)
            return res;
        container.resize(count);
        return (*function)(std::forward<Args>(args)..., &count, container.data());
    }

    /** @brief Fill a container using a vulkan style getter with void as return type */
    template<typename Container, typename ...FunctionArgs, typename ...Args>
    void FillVkContainer(Container &container, void(*function)(FunctionArgs...), Args &&...args)
    {
        std::uint32_t count = 0;
        (*function)(std::forward<Args>(args)..., &count, nullptr);
        if (!count) [[unlikely]]
            return;
        container.resize(count);
        (*function)(std::forward<Args>(args)..., &count, container.data());
    }

}