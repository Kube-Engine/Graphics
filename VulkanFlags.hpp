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


    /** @brief Pipeline layout creation flags */
    enum class PipelineLayoutCreateFlags : VkPipelineLayoutCreateFlags {
        None = 0x0
    };


    /** @brief Frame buffer creation flags */
    enum class FramebufferCreateFlags : VkFramebufferCreateFlags {
        None = 0x0,
        Imageless = VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT,
        ImagelessKhr = VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT_KHR
    };


    /** @brief Buffer creation flags */
    enum class BufferCreateFlags : VkBufferCreateFlags {
        None = 0x0,
        SparseBinding = VK_BUFFER_CREATE_SPARSE_BINDING_BIT,
        SparseResidency = VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT,
        SparseAliased = VK_BUFFER_CREATE_SPARSE_ALIASED_BIT,
        Protected = VK_BUFFER_CREATE_PROTECTED_BIT,
        DeviceAddressCaptureReplay = VK_BUFFER_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT,
        DeviceAddressCaptureReplayExt = VK_BUFFER_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT_EXT,
        DeviceAddressCaptureReplayKhr = VK_BUFFER_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT_KHR
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
        ShaderDeviceAddress = VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT,
        TransformFeedbackBufferExt = VK_BUFFER_USAGE_TRANSFORM_FEEDBACK_BUFFER_BIT_EXT,
        TransformFeedbackCounterBufferExt = VK_BUFFER_USAGE_TRANSFORM_FEEDBACK_COUNTER_BUFFER_BIT_EXT,
        ConditionalRenderingExt = VK_BUFFER_USAGE_CONDITIONAL_RENDERING_BIT_EXT,
        RayTracingKhr = VK_BUFFER_USAGE_RAY_TRACING_BIT_KHR,
        RayTracingNv = VK_BUFFER_USAGE_RAY_TRACING_BIT_NV,
        ShaderDeviceAddressExt = VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT_EXT,
        ShaderDeviceAddressKhr = VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT_KHR
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
        Disjoint = VK_IMAGE_CREATE_DISJOINT_BIT,
        CornerSampledNv = VK_IMAGE_CREATE_CORNER_SAMPLED_BIT_NV,
        SampleLocationsCompatibleDepthExt = VK_IMAGE_CREATE_SAMPLE_LOCATIONS_COMPATIBLE_DEPTH_BIT_EXT,
        SubsampledExt = VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT,
        SplitInstanceBindRegionsKhr = VK_IMAGE_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT_KHR,
        Array2DCompatibleKhr = VK_IMAGE_CREATE_2D_ARRAY_COMPATIBLE_BIT_KHR,
        BlockTexelViewCompatibleKhr = VK_IMAGE_CREATE_BLOCK_TEXEL_VIEW_COMPATIBLE_BIT_KHR,
        ExtendedUsageKhr = VK_IMAGE_CREATE_EXTENDED_USAGE_BIT_KHR,
        DisjointKhr = VK_IMAGE_CREATE_DISJOINT_BIT_KHR,
        AliasKhr = VK_IMAGE_CREATE_ALIAS_BIT_KHR
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
        InputAttachment = VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT,
        ShadingRateImageNv = VK_IMAGE_USAGE_SHADING_RATE_IMAGE_BIT_NV,
        FragmentDensityMapExt = VK_IMAGE_USAGE_FRAGMENT_DENSITY_MAP_BIT_EXT
    };

    /** @brief Sample count flags */
    enum class SampleCountFlags : VkSampleCountFlags {
        X1 = VK_SAMPLE_COUNT_1_BIT,
        X2 = VK_SAMPLE_COUNT_2_BIT,
        X4 = VK_SAMPLE_COUNT_4_BIT,
        X8 = VK_SAMPLE_COUNT_8_BIT,
        X16 = VK_SAMPLE_COUNT_16_BIT,
        X32 = VK_SAMPLE_COUNT_32_BIT,
        X64 = VK_SAMPLE_COUNT_64_BIT
    };


    /** @brief Image view creation flags */
    enum class ImageViewCreateFlags : VkImageViewCreateFlags {
        None = 0x0,
        Dynamic = VK_IMAGE_VIEW_CREATE_FRAGMENT_DENSITY_MAP_DYNAMIC_BIT_EXT,
        Defered = VK_IMAGE_VIEW_CREATE_FRAGMENT_DENSITY_MAP_DEFERRED_BIT_EXT
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
        DispatchBase = VK_PIPELINE_CREATE_DISPATCH_BASE_BIT,
        RayTracingNoNullAnyHitShadersKhr = VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_ANY_HIT_SHADERS_BIT_KHR,
        RayTracingNoNullClosestHitShadersKhr = VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_CLOSEST_HIT_SHADERS_BIT_KHR,
        RayTracingNoNullMissShadersKhr = VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_MISS_SHADERS_BIT_KHR,
        RayTracingNoNullIntersectionShadersKhr = VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_INTERSECTION_SHADERS_BIT_KHR,
        RayTracingSkipTrianglesKhr = VK_PIPELINE_CREATE_RAY_TRACING_SKIP_TRIANGLES_BIT_KHR,
        RayTracingSkipAabbsKhr = VK_PIPELINE_CREATE_RAY_TRACING_SKIP_AABBS_BIT_KHR,
        DeferCompileNv = VK_PIPELINE_CREATE_DEFER_COMPILE_BIT_NV,
        CaptureStatisticsKhr = VK_PIPELINE_CREATE_CAPTURE_STATISTICS_BIT_KHR,
        CaptureInternalRepresentationsKhr = VK_PIPELINE_CREATE_CAPTURE_INTERNAL_REPRESENTATIONS_BIT_KHR,
        IndirectBindableNv = VK_PIPELINE_CREATE_INDIRECT_BINDABLE_BIT_NV,
        LibraryKhr = VK_PIPELINE_CREATE_LIBRARY_BIT_KHR,
        FailOnPipelineCompileRequiredExt = VK_PIPELINE_CREATE_FAIL_ON_PIPELINE_COMPILE_REQUIRED_BIT_EXT,
        EarlyReturnOnFailureExt = VK_PIPELINE_CREATE_EARLY_RETURN_ON_FAILURE_BIT_EXT,
        DispatchBase = VK_PIPELINE_CREATE_DISPATCH_BASE,
        ViewIndexFromDeviceIndexKhr = VK_PIPELINE_CREATE_VIEW_INDEX_FROM_DEVICE_INDEX_BIT_KHR,
        DispatchBaseKhr = VK_PIPELINE_CREATE_DISPATCH_BASE_KHR
    };

    /** @brief Vertex input state creation flags */
    enum class VertexInputCreateFlags : VkPipelineVertexInputStateCreateFlags {
        None = 0x0
    };


    /** @brief Shader stage creation flags */
    enum class ShaderStageCreateFlags : VkPipelineShaderStageCreateFlags {
        None = 0x0,
        AllowVaryingSubgroupSizeExt = VK_PIPELINE_SHADER_STAGE_CREATE_ALLOW_VARYING_SUBGROUP_SIZE_BIT_EXT,
        RequireFullSubgroupsExt = VK_PIPELINE_SHADER_STAGE_CREATE_REQUIRE_FULL_SUBGROUPS_BIT_EXT
    };

    /** @brief Shader stage flags */
    enum class ShaderStageFlags : VkShaderStageFlags {
        None = 0x0,
        VertexBit = VK_SHADER_STAGE_VERTEX_BIT,
        TessellationControlBit = VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT,
        TessellationEvaluationBit = VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT,
        GeometryBit = VK_SHADER_STAGE_GEOMETRY_BIT,
        FragmentBit = VK_SHADER_STAGE_FRAGMENT_BIT,
        ComputeBit = VK_SHADER_STAGE_COMPUTE_BIT,
        AllGraphics = VK_SHADER_STAGE_ALL_GRAPHICS,
        All = VK_SHADER_STAGE_ALL,
        RaygenBitKhr = VK_SHADER_STAGE_RAYGEN_BIT_KHR,
        AnyHitBitKhr = VK_SHADER_STAGE_ANY_HIT_BIT_KHR,
        ClosestHitBitKhr = VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR,
        MissBitKhr = VK_SHADER_STAGE_MISS_BIT_KHR,
        IntersectionBitKhr = VK_SHADER_STAGE_INTERSECTION_BIT_KHR,
        CallableBitKhr = VK_SHADER_STAGE_CALLABLE_BIT_KHR,
        TaskBitNv = VK_SHADER_STAGE_TASK_BIT_NV,
        MeshBitNv = VK_SHADER_STAGE_MESH_BIT_NV,
        RaygenBitNv = RaygenBitKhr,
        AnyHitBitNv = AnyHitBitKhr,
        ClosestHitBitNv = ClosestHitBitKhr,
        MissBitNv = MissBitKhr,
        IntersectionBitNv = IntersectionBitKhr,
        CallableBitNv = CallableBitKhr
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
        None = 0x0
    };


    /** @brief Multisample creation flags */
    enum class MultisampleCreateFlags : VkPipelineMultisampleStateCreateFlags {
        None = 0x0,
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
        A = VK_COLOR_COMPONENT_A_BIT
    };


    /** @brief Dynamic state creation flags */
    enum class DynamicStateCreateFlags : VkPipelineDynamicStateCreateFlags {
        None = 0x0
    };


    /** @brief Descriptor set layout creation flags */
    enum class DescriptorSetLayoutCreateFlags : VkDescriptorSetLayoutCreateFlags {
        None = 0x0,
        UpdateAfterBindPool = VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT,
        PushDescriptorKhr = VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR,
        UpdateAfterBindPoolExt = VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT_EXT
    };

    /** @brief Descriptor pool creation flags */
    enum class DescriptorPoolCreateFlags : VkDescriptorPoolCreateFlags {
        None = 0x0,
        FreeDescriptorSet = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT,
        UpdateAfterBind = VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT,
        UpdateAfterBindBit = UpdateAfterBind,
    };
}
