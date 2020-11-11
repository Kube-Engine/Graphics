/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Vulkan flags
 */

#include <vulkan/vulkan.h>
#include <vk_mem_alloc.h>

namespace kF::Graphics
{
    /** @brief Any flag base */
    using Flags = VkFlags;

    /** @brief Helper used to combine protected enum flags */
    template<typename FlagsType, FlagsType ...Values> requires std::convertible_to<FlagsType, Flags>
    [[nodiscard]] constexpr Flags MakeFlags(Values ...values) noexcept
        { return ... | static_cast<Flags>(values); }


    /** @brief Describes all types of queues */
    enum class QueueType : VkQueueFlags {
        Graphics = VK_QUEUE_GRAPHICS_BIT,
        Compute = VK_QUEUE_COMPUTE_BIT,
        Transfer = VK_QUEUE_TRANSFER_BIT,
        SparseBinding = VK_QUEUE_SPARSE_BINDING_BIT,
        Protected = VK_QUEUE_PROTECTED_BIT,
        Present,
        Count
    };


    /** @brief Frame buffer creation flags */
    enum class FrameBufferCreateFlags : VkFramebufferCreateFlags {
        None = 0x0,
        Imageless = VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT,
        ImagelessKhr = VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT_KHR
    };


    /** @brief Buffer creation flags */
    enum class BufferCreateFlags : VkBufferCreateFlags {
        None = 0x0,
        SparseBindingBit = VK_BUFFER_CREATE_SPARSE_BINDING_BIT,
        SparseResidencyBit = VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT,
        SparseAliasedBit = VK_BUFFER_CREATE_SPARSE_ALIASED_BIT,
        ProtectedBit = VK_BUFFER_CREATE_PROTECTED_BIT,
        DeviceAddressCaptureReplayBit = VK_BUFFER_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT,
        DeviceAddressCaptureReplayBitExt = VK_BUFFER_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT_EXT,
        DeviceAddressCaptureReplayBitKhr = VK_BUFFER_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT_KHR
    };

    /** @brief Buffer usage flags */
    enum class BufferUsageFlags : VkBufferUsageFlags {
        TransferSrcBit = VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        TransferDstBit = VK_BUFFER_USAGE_TRANSFER_DST_BIT,
        UniformTexelBufferBit = VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT,
        StorageTexelBufferBit = VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT,
        UniformBufferBit = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
        StorageBufferBit = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
        IndexBufferBit = VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
        VertexBufferBit = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
        IndirectBufferBit = VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT,
        ShaderDeviceAddressBit = VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT,
        TransformFeedbackBufferBitExt = VK_BUFFER_USAGE_TRANSFORM_FEEDBACK_BUFFER_BIT_EXT,
        TransformFeedbackCounterBufferBitExt = VK_BUFFER_USAGE_TRANSFORM_FEEDBACK_COUNTER_BUFFER_BIT_EXT,
        ConditionalRenderingBitExt = VK_BUFFER_USAGE_CONDITIONAL_RENDERING_BIT_EXT,
        RayTracingBitKhr = VK_BUFFER_USAGE_RAY_TRACING_BIT_KHR,
        RayTracingBitNv = VK_BUFFER_USAGE_RAY_TRACING_BIT_NV,
        ShaderDeviceAddressBitExt = VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT_EXT,
        ShaderDeviceAddressBitKhr = VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT_KHR
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
        TransferSrcBit = VK_IMAGE_USAGE_TRANSFER_SRC_BIT,
        TransferDstBit = VK_IMAGE_USAGE_TRANSFER_DST_BIT,
        SampledBit = VK_IMAGE_USAGE_SAMPLED_BIT,
        StorageBit = VK_IMAGE_USAGE_STORAGE_BIT,
        ColorAttachmentBit = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
        DepthStencilAttachmentBit = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
        TransientAttachmentBit = VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT,
        InputAttachmentBit = VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT,
        ShadingRateImageBitNv = VK_IMAGE_USAGE_SHADING_RATE_IMAGE_BIT_NV,
        FragmentDensityMapBitExt = VK_IMAGE_USAGE_FRAGMENT_DENSITY_MAP_BIT_EXT
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



}