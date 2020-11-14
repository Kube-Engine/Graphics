/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Vulkan utils
 */

#pragma once

#include <Kube/Core/Utils.hpp>

#include "VulkanEnums.hpp"

namespace kF::Graphics
{
    VK_DEFINE_HANDLE(Handle)

    /** @brief Null handle alias */
    constexpr auto NullHandle = nullptr;

    /** @brief Index of a frame */
    using FrameIndex = std::size_t;


    /** @brief Instance handle */
    using InstanceHandle = VkInstance;


    /** @brief Physical device handle */
    using PhysicalDeviceHandle = VkPhysicalDevice;


    /** @brief Logical device handle */
    using LogicalDeviceHandle = VkDevice;


    /** @brief 2D extent */
    using Extent2D = VkExtent2D;

    /** @brief 3D extent */
    using Extent3D = VkExtent3D;


    /** @brief Swapchain handle */
    using SwapchainHandle = VkSwapchainKHR;


    /** @brief Surface handle */
    using SurfaceHandle = VkSurfaceKHR;

    /** @brief Vulkan surface format */
    using SurfaceFormat = VkSurfaceFormatKHR;

    /** @brief Vulkan presentation mode*/
    using SurfaceCapabilities = VkSurfaceCapabilitiesKHR;


    /** @brief Fence handle */
    using FenceHandle = VkFence;

    /** @brief Fence handle */
    using SemaphoreHandle = VkFence;


    /** @brief Pipeline layout handle */
    using PipelineLayoutHandle = VkPipelineLayout;

    /** @brief Descriptor set layout handle */
    using DescriptorSetLayoutHandle = VkDescriptorSetLayout;

    /** @brief Descriptor set handle */
    using DescriptorSet = VkDescriptorSet;

    /** @brief Descriptor set write handle */
    using DescriptorSetWrite = VkWriteDescriptorSet;

    /** @brief Descriptor buffer info */
    using DescriptorBufferInfo = VkDescriptorBufferInfo;

    /** @brief Descriptor buffer info */
    using DescriptorImageInfo = VkDescriptorImageInfo;

    /** @brief Push constant range */
    using PushConstantRange = VkPushConstantRange;


    /** @brief Vertex input binding description */
    using VertexInputBinding = VkVertexInputBindingDescription;

    /** @brief Vertex input attribute description */
    using VertexInputAttribute = VkVertexInputAttributeDescription;


    /** @brief Render pass handle */
    using RenderPassHandle = VkRenderPass;


    /** @brief A frame buffer handle */
    using FramebufferHandle = VkFramebuffer;


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

    /** @brief Buffer view handle */
    using BufferViewHandle = VkBufferView;


    /** @brief Image handle */
    using ImageHandle = VkImage;

    /** @brief Image view handle */
    using ImageViewHandle = VkImageView;

    /** @brief Image subresource range */
    using ImageSubresourceRange = VkImageSubresourceRange;

    /** @brief Component mapping */
    using ComponentMapping = VkComponentMapping;


    /** @brief Sampler handle */
    using SamplerHandle = VkSampler;


    /** @brief Vertex input binding description */
    using VertexInputBindingDescription = VkVertexInputBindingDescription;

    /** @brief Vertex input attribute description */
    using VertexInputAttributeDescription = VkVertexInputAttributeDescription;


    /** @brief Shader module */
    using ShaderModuleHandle = VkShaderModule;

    /** @brief Shader specialization info */
    using ShaderSpecializationTable = VkSpecializationInfo;


    /** @brief Sample mask */
    using SampleMask = VkSampleMask;


    /** @brief Stencil operation state */
    using StencilOpState = VkStencilOpState;


    /** @brief Color blend attachment state */
    using ColorBlendAttachmentState = VkPipelineColorBlendAttachmentState;


    /** @brief Get an error message from a vulkan result */
    [[nodiscard]] const char *ErrorMessage(const VkResult res);

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
    auto FillVkContainer(Container &container, void(*function)(FunctionArgs...), Args &&...args)
    {
        std::uint32_t count = 0;
        (*function)(std::forward<Args>(args)..., &count, nullptr);
        if (!count) [[unlikely]]
            return;
        container.resize(count);
        (*function)(std::forward<Args>(args)..., &count, container.data());
    }

}