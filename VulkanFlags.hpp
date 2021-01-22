/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Vulkan flags
 */

#include <vulkan/vulkan.h>
#include <vk_mem_alloc.h>

#include <concepts>

namespace kF::Graphics
{
    /** @brief Any flag base */
    using Flags = VkFlags;

    /** @brief Helper used to combine protected enum flags */
    template<typename FlagsType, typename ...Values> requires std::conjunction_v<std::is_same<Values, FlagsType>...>
    [[nodiscard]] constexpr FlagsType MakeFlags(const FlagsType first, Values ...following) noexcept
        { return static_cast<FlagsType>((ToFlags(first) | ... | ToFlags(following))); }

    /** @brief Helper used to combine protected enum flags */
    template<typename FlagsType> requires requires { static_cast<Flags>(std::declval<FlagsType>()); }
    [[nodiscard]] constexpr Flags ToFlags(const FlagsType value) noexcept
        { return static_cast<Flags>(value); }


    /** @brief Queue flags */
    enum class QueueFlags : VkQueueFlags {
        None = 0x0,
        Graphics = VK_QUEUE_GRAPHICS_BIT,
        Compute = VK_QUEUE_COMPUTE_BIT,
        Transfer = VK_QUEUE_TRANSFER_BIT,
        SparseBinding = VK_QUEUE_SPARSE_BINDING_BIT,
        Protected = VK_QUEUE_PROTECTED_BIT
    };


    /** @brief Pipeline stage flags */
    enum PipelineStageFlags : VkPipelineStageFlags {
        None = 0x0,
        TopOfPipe = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
        DrawIndirect = VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT,
        VertexInput = VK_PIPELINE_STAGE_VERTEX_INPUT_BIT,
        VertexShader = VK_PIPELINE_STAGE_VERTEX_SHADER_BIT,
        TessellationControlShader = VK_PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT,
        TessellationEvaluationShader = VK_PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT,
        GeometryShader = VK_PIPELINE_STAGE_GEOMETRY_SHADER_BIT,
        FragmentShader = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
        EarlyFragmentTests = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT,
        LateFragmentTests = VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT,
        ColorAttachmentOutput = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        ComputeShader = VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
        Transfer = VK_PIPELINE_STAGE_TRANSFER_BIT,
        BottomOfPipe = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
        Host = VK_PIPELINE_STAGE_HOST_BIT,
        AllGraphics = VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT,
        AllCommands = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT
    };


    /** @brief Pipeline layout creation flags */
    enum class PipelineLayoutCreateFlags : VkPipelineLayoutCreateFlags {
        None = 0x0
    };


    /** @brief Frame buffer creation flags */
    enum class FramebufferCreateFlags : VkFramebufferCreateFlags {
        None = 0x0,
        Imageless = VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT
    };


    /** @brief Buffer creation flags */
    enum class BufferCreateFlags : VkBufferCreateFlags {
        None = 0x0,
        SparseBinding = VK_BUFFER_CREATE_SPARSE_BINDING_BIT,
        SparseResidency = VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT,
        SparseAliased = VK_BUFFER_CREATE_SPARSE_ALIASED_BIT,
        Protected = VK_BUFFER_CREATE_PROTECTED_BIT,
        DeviceAddressCaptureReplay = VK_BUFFER_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT
    };

    /** @brief Buffer usage flags */
    enum class BufferUsageFlags : VkBufferUsageFlags {
        TransferSrc = VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        TransferDst = VK_BUFFER_USAGE_TRANSFER_DST_BIT,
        UniformTexelBuffer = VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT,
        StorageTexelBuffer = VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT,
        UniformBuffer = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
        StorageBuffer = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
        IndexBuffer = VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
        VertexBuffer = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
        IndirectBuffer = VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT,
        ShaderDeviceAddress = VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT
    };


    /** @brief Image creation flags */
    enum class ImageCreateFlags : VkImageCreateFlags {
        None = 0x0,
        SparseBinding = VK_IMAGE_CREATE_SPARSE_BINDING_BIT,
        SparseResidency = VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT,
        SparseAliased = VK_IMAGE_CREATE_SPARSE_ALIASED_BIT,
        MutableFormat = VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT,
        CubeCompatible = VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT,
        Alias = VK_IMAGE_CREATE_ALIAS_BIT,
        SplitInstanceBindRegions = VK_IMAGE_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT,
        Array2DCompatible = VK_IMAGE_CREATE_2D_ARRAY_COMPATIBLE_BIT,
        BlockTexelViewCompatible = VK_IMAGE_CREATE_BLOCK_TEXEL_VIEW_COMPATIBLE_BIT,
        ExtendedUsage = VK_IMAGE_CREATE_EXTENDED_USAGE_BIT,
        Protected = VK_IMAGE_CREATE_PROTECTED_BIT,
        Disjoint = VK_IMAGE_CREATE_DISJOINT_BIT
    };

    /** @brief Image usage flags */
    enum class ImageUsageFlags : VkImageUsageFlags {
        TransferSrc = VK_IMAGE_USAGE_TRANSFER_SRC_BIT,
        TransferDst = VK_IMAGE_USAGE_TRANSFER_DST_BIT,
        Sampled = VK_IMAGE_USAGE_SAMPLED_BIT,
        Storage = VK_IMAGE_USAGE_STORAGE_BIT,
        ColorAttachment = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
        DepthStencilAttachment = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
        TransientAttachment = VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT,
        InputAttachment = VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT
    };


    /** @brief Image view creation flags */
    enum class ImageViewCreateFlags : VkImageViewCreateFlags {
        None = 0x0,
        Dynamic = VK_IMAGE_VIEW_CREATE_FRAGMENT_DENSITY_MAP_DYNAMIC_BIT_EXT
    };

    /** @brief Sampler creation flags */
    enum class SamplerCreateFlags : VkSamplerCreateFlags {
        None = 0x0,
        SubsampledExt = VK_SAMPLER_CREATE_SUBSAMPLED_BIT_EXT,
        SubsampledCoarseReconstructionExt = VK_SAMPLER_CREATE_SUBSAMPLED_COARSE_RECONSTRUCTION_BIT_EXT
    };


    /** @brief Command buffer usage flags */
    enum class CommandBufferUsageFlags : VkCommandBufferUsageFlags {
        None = 0x0,
        OneTimeSubmit = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
        RenderPassContinue = VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT,
        SimultaneousUse = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT
    };


    /** @brief Pipeline creation flags */
    enum class PipelineCreateFlags : VkPipelineCreateFlags {
        None = 0x0,
        DisableOptimization = VK_PIPELINE_CREATE_DISABLE_OPTIMIZATION_BIT,
        AllowDerivatives = VK_PIPELINE_CREATE_ALLOW_DERIVATIVES_BIT,
        Derivative = VK_PIPELINE_CREATE_DERIVATIVE_BIT,
        ViewIndexFromDeviceIndex = VK_PIPELINE_CREATE_VIEW_INDEX_FROM_DEVICE_INDEX_BIT,
        DispatchBase = VK_PIPELINE_CREATE_DISPATCH_BASE_BIT
    };

    /** @brief Vertex input state creation flags */
    enum class VertexInputCreateFlags : VkPipelineVertexInputStateCreateFlags {
        None = 0x0
    };


    /** @brief Shader stage creation flags */
    enum class ShaderStageCreateFlags : VkPipelineShaderStageCreateFlags {
        None = 0x0
    };

    /** @brief Shader stage flags */
    enum class ShaderStageFlags : VkShaderStageFlags {
        None = 0x0,
        Vertex = VK_SHADER_STAGE_VERTEX_BIT,
        TessellationControl = VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT,
        TessellationEvaluation = VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT,
        Geometry = VK_SHADER_STAGE_GEOMETRY_BIT,
        Fragment = VK_SHADER_STAGE_FRAGMENT_BIT,
        Compute = VK_SHADER_STAGE_COMPUTE_BIT,
        AllGraphics = VK_SHADER_STAGE_ALL_GRAPHICS,
        All = VK_SHADER_STAGE_ALL
    };


    /** @brief Input assembly creation flags */
    enum class InputAssemblyCreateFlags : VkPipelineInputAssemblyStateCreateFlags {
        None = 0x0
    };


    /** @brief Tessellation state assembly creation flags */
    enum class TessellationCreateFlags : VkPipelineTessellationStateCreateFlags{
        None = 0x0
    };


    /** @brief Viewport creation flags */
    enum class ViewportCreateFlags : VkPipelineViewportStateCreateFlags {
        None = 0x0
    };


    /** @brief Rasterization creation flags */
    enum class RasterizationCreateFlags : VkPipelineRasterizationStateCreateFlags {
        None = 0x0
    };

    /** @brief Cull mode flags */
    enum class CullModeFlags : VkCullModeFlags {
        None = 0x0,
        Front = VK_CULL_MODE_FRONT_BIT,
        Back = VK_CULL_MODE_BACK_BIT,
        FrontAndBack = VK_CULL_MODE_FRONT_AND_BACK
    };


    /** @brief Multisample creation flags */
    enum class MultisampleCreateFlags : VkPipelineMultisampleStateCreateFlags {
        None = 0x0
    };

    /** @brief Sample count flags */
    enum class SampleCountFlags : VkSampleCountFlags {
        None = 0x0,
        X1 = VK_SAMPLE_COUNT_1_BIT,
        X2 = VK_SAMPLE_COUNT_2_BIT,
        X4 = VK_SAMPLE_COUNT_4_BIT,
        X8 = VK_SAMPLE_COUNT_8_BIT,
        X16 = VK_SAMPLE_COUNT_16_BIT,
        X32 = VK_SAMPLE_COUNT_32_BIT,
        X64 = VK_SAMPLE_COUNT_64_BIT
    };


    /** @brief Depth stencil creation flags */
    enum class DepthStencilCreateFlags : VkPipelineDepthStencilStateCreateFlags {
        None = 0x0
    };


    /** @brief Color blend creation flags */
    enum class ColorBlendCreateFlags : VkPipelineColorBlendStateCreateFlags {
        None = 0x0
    };

    /** @brief Color components flags */
    enum class ColorComponentFlags : VkColorComponentFlags {
        None = 0x0,
        R = VK_COLOR_COMPONENT_R_BIT,
        G = VK_COLOR_COMPONENT_G_BIT,
        B = VK_COLOR_COMPONENT_B_BIT,
        A = VK_COLOR_COMPONENT_A_BIT,
        RGBA = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT
    };


    /** @brief Dynamic state creation flags */
    enum class DynamicStateCreateFlags : VkPipelineDynamicStateCreateFlags {
        None = 0x0
    };


    /** @brief Descriptor set layout creation flags */
    enum class DescriptorSetLayoutCreateFlags : VkDescriptorSetLayoutCreateFlags {
        None = 0x0,
        UpdateAfterBindPool = VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT
    };

    /** @brief Descriptor pool creation flags */
    enum class DescriptorPoolCreateFlags : VkDescriptorPoolCreateFlags {
        None = 0x0,
        FreeDescriptorSet = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT,
        UpdateAfterBind = VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT
    };
}
