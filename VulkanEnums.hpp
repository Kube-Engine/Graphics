/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Format
 */

#pragma once

#include "VulkanFlags.hpp"

namespace kF::Graphics
{
    /** @brief Describes all supported queue types */
    enum class QueueType : std::size_t {
        Graphics = 0u,
        Compute,
        Transfer,
        Present,
        Count
    };

    /** @brief Presentation mode */
    enum class PresentMode {
        ImmediateKhr = VK_PRESENT_MODE_IMMEDIATE_KHR,
        MailboxKhr = VK_PRESENT_MODE_MAILBOX_KHR,
        FifoKhr = VK_PRESENT_MODE_FIFO_KHR,
        FifoRelaxedKhr = VK_PRESENT_MODE_FIFO_RELAXED_KHR,
        SharedDemandRefreshKhr = VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR,
        SharedContinuousRefreshKhr = VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR
    };


    /** @brief Memory usage */
    enum class MemoryUsage {
        Unknown = VMA_MEMORY_USAGE_UNKNOWN,
        GpuOnly = VMA_MEMORY_USAGE_GPU_ONLY,
        CpuOnly = VMA_MEMORY_USAGE_CPU_ONLY,
        CpuToGpu = VMA_MEMORY_USAGE_CPU_TO_GPU,
        GpuToCpu = VMA_MEMORY_USAGE_GPU_TO_CPU,
        CpuCopy = VMA_MEMORY_USAGE_CPU_COPY,
        GpuLazilyAllocated = VMA_MEMORY_USAGE_GPU_LAZILY_ALLOCATED
    };


    /** @brief Descriptor type */
    enum class DescriptorType {
        Sampler = VK_DESCRIPTOR_TYPE_SAMPLER,
        SampledImage = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,
        CombinedImageSampler = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
        StorageImage = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,
        UniformTexelBuffer = VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER,
        StorageTexelBuffer = VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER,
        UniformBuffer = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        StorageBuffer = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
        UniformBufferDynamic = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC,
        StorageBufferDynamic = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC,
        InputAttachment = VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT,
        InlineUniformBlockExt = VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK_EXT,
        AccelerationStructureKhr = VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR,
        AccelerationStructureNv = AccelerationStructureKhr
    };


    /** @brief Command buffer level */
    enum class CommandLevel {
        Primary = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        Secondary = VK_COMMAND_BUFFER_LEVEL_SECONDARY
    };


    /** @brief Sharing mode */
    enum class SharingMode {
        Exclusive = VK_SHARING_MODE_EXCLUSIVE,
        Concurrent = VK_SHARING_MODE_CONCURRENT
    };


    /** @brief Image tiling */
    enum class ImageTiling {
        TilingOptimal = VK_IMAGE_TILING_OPTIMAL,
        TilingLinear = VK_IMAGE_TILING_LINEAR,
        TilingDrmFormatModifierExt = VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT
    };

    /** @brief Image type */
    enum class ImageType {
        Type1D = VK_IMAGE_TYPE_1D,
        Type2D = VK_IMAGE_TYPE_2D,
        Type3D = VK_IMAGE_TYPE_3D
    };

    /** @brief Image view type */
    enum class ImageViewType {
        Image1D = VK_IMAGE_VIEW_TYPE_1D,
        Image2D = VK_IMAGE_VIEW_TYPE_2D,
        Image3D = VK_IMAGE_VIEW_TYPE_3D,
        Cube = VK_IMAGE_VIEW_TYPE_CUBE,
        Array1D = VK_IMAGE_VIEW_TYPE_1D_ARRAY,
        Array2D = VK_IMAGE_VIEW_TYPE_2D_ARRAY,
        ArrayCube = VK_IMAGE_VIEW_TYPE_CUBE_ARRAY
    };

    /** @brief Image layout */
    enum class ImageLayout {
        Undefined = VK_IMAGE_LAYOUT_UNDEFINED,
        General = VK_IMAGE_LAYOUT_GENERAL,
        ColorAttachmentOptimal = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
        DepthStencilAttachmentOptimal = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
        DepthStencilReadOnlyOptimal = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL,
        ShaderReadOnlyOptimal = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
        TransferSrcOptimal = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
        TransferDstOptimal = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
        Preinitialized = VK_IMAGE_LAYOUT_PREINITIALIZED,
        DepthReadOnlyStencilAttachmentOptimal = VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL,
        DepthAttachmentStencilReadOnlyOptimal = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL,
        DepthAttachmentOptimal = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL,
        DepthReadOnlyOptimal = VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL,
        StencilAttachmentOptimal = VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL,
        StencilReadOnlyOptimal = VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL,
        PresentSrcKhr = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
        SharedPresentKhr = VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR,
        ShadingRateOptimalNv = VK_IMAGE_LAYOUT_SHADING_RATE_OPTIMAL_NV,
        FragmentDensityMapOptimalExt = VK_IMAGE_LAYOUT_FRAGMENT_DENSITY_MAP_OPTIMAL_EXT,
        DepthReadOnlyStencilAttachmentOptimalKhr = VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL_KHR,
        DepthAttachmentStencilReadOnlyOptimalKhr = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL_KHR,
        DepthAttachmentOptimalKhr = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL_KHR,
        DepthReadOnlyOptimalKhr = VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL_KHR,
        StencilAttachmentOptimalKhr = VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL_KHR,
        StencilReadOnlyOptimalKhr = VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL_KHR,
    };


    /** @brief Sampler mimap mode */
    enum class SamplerMipmapMode {
        Nearest = VK_SAMPLER_MIPMAP_MODE_NEAREST,
        Linear = VK_SAMPLER_MIPMAP_MODE_LINEAR
    };

    /** @brief Sampler adress mode */
    enum class SamplerAddressMode {
        Repeat = VK_SAMPLER_ADDRESS_MODE_REPEAT,
        MirroredRepeat = VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT,
        ClampToEdge = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
        ClampToBorder = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER,
        MirrorClampToEdge = VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE,
        MirrorClampToEdgeKhr = VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE_KHR,
    };


    /** @brief Sampler filter */
    enum class Filter {
        Nearest = VK_FILTER_NEAREST,
        Linear = VK_FILTER_LINEAR,
        CubicImg = VK_FILTER_CUBIC_IMG,
        CubicExt = VK_FILTER_CUBIC_EXT
    };

    /** @brief Compare operators */
    enum class CompareOp {
        Never = VK_COMPARE_OP_NEVER,
        Less = VK_COMPARE_OP_LESS,
        Equal = VK_COMPARE_OP_EQUAL,
        LessOrEqual = VK_COMPARE_OP_LESS_OR_EQUAL,
        Greater = VK_COMPARE_OP_GREATER,
        NotEqual = VK_COMPARE_OP_NOT_EQUAL,
        GreaterOrEqual = VK_COMPARE_OP_GREATER_OR_EQUAL,
        Always = VK_COMPARE_OP_ALWAYS
    };

    /** @brief Logic operators */
    enum class LogicOp {
        Clear = VK_LOGIC_OP_CLEAR,
        And = VK_LOGIC_OP_AND,
        AndReverse = VK_LOGIC_OP_AND_REVERSE,
        Copy = VK_LOGIC_OP_COPY,
        AndInverted = VK_LOGIC_OP_AND_INVERTED,
        NoOp = VK_LOGIC_OP_NO_OP,
        Xor = VK_LOGIC_OP_XOR,
        Or = VK_LOGIC_OP_OR,
        Nor = VK_LOGIC_OP_NOR,
        Equivalent = VK_LOGIC_OP_EQUIVALENT,
        Invert = VK_LOGIC_OP_INVERT,
        OrReverse = VK_LOGIC_OP_OR_REVERSE,
        CopyInverted = VK_LOGIC_OP_COPY_INVERTED,
        OrInverted = VK_LOGIC_OP_OR_INVERTED,
        Nand = VK_LOGIC_OP_NAND,
        Set = VK_LOGIC_OP_SET,
    };

    /** @brief Stencil operators */
    enum class StencilOp {
        Keep = VK_STENCIL_OP_KEEP,
        Zero = VK_STENCIL_OP_ZERO,
        Replace = VK_STENCIL_OP_REPLACE,
        IncrementAndClamp = VK_STENCIL_OP_INCREMENT_AND_CLAMP,
        DecrementAndClamp = VK_STENCIL_OP_DECREMENT_AND_CLAMP,
        Invert = VK_STENCIL_OP_INVERT,
        IncrementAndWrap = VK_STENCIL_OP_INCREMENT_AND_WRAP,
        DecrementAndWrap = VK_STENCIL_OP_DECREMENT_AND_WRAP
    };

    /** @brief Blend operators */
    enum class BlendOp {
        Add = VK_BLEND_OP_ADD,
        Subtract = VK_BLEND_OP_SUBTRACT,
        ReverseSubtract = VK_BLEND_OP_REVERSE_SUBTRACT,
        Min = VK_BLEND_OP_MIN,
        Max = VK_BLEND_OP_MAX,
        ZeroExt = VK_BLEND_OP_ZERO_EXT,
        SrcExt = VK_BLEND_OP_SRC_EXT,
        DstExt = VK_BLEND_OP_DST_EXT,
        SrcOverExt = VK_BLEND_OP_SRC_OVER_EXT,
        DstOverExt = VK_BLEND_OP_DST_OVER_EXT,
        SrcInExt = VK_BLEND_OP_SRC_IN_EXT,
        DstInExt = VK_BLEND_OP_DST_IN_EXT,
        SrcOutExt = VK_BLEND_OP_SRC_OUT_EXT,
        DstOutExt = VK_BLEND_OP_DST_OUT_EXT,
        SrcAtopExt = VK_BLEND_OP_SRC_ATOP_EXT,
        DstAtopExt = VK_BLEND_OP_DST_ATOP_EXT,
        XorExt = VK_BLEND_OP_XOR_EXT,
        MultiplyExt = VK_BLEND_OP_MULTIPLY_EXT,
        ScreenExt = VK_BLEND_OP_SCREEN_EXT,
        OverlayExt = VK_BLEND_OP_OVERLAY_EXT,
        DarkenExt = VK_BLEND_OP_DARKEN_EXT,
        LightenExt = VK_BLEND_OP_LIGHTEN_EXT,
        ColordodgeExt = VK_BLEND_OP_COLORDODGE_EXT,
        ColorburnExt = VK_BLEND_OP_COLORBURN_EXT,
        HardlightExt = VK_BLEND_OP_HARDLIGHT_EXT,
        SoftlightExt = VK_BLEND_OP_SOFTLIGHT_EXT,
        DifferenceExt = VK_BLEND_OP_DIFFERENCE_EXT,
        ExclusionExt = VK_BLEND_OP_EXCLUSION_EXT,
        InvertExt = VK_BLEND_OP_INVERT_EXT,
        InvertRgbExt = VK_BLEND_OP_INVERT_RGB_EXT,
        LineardodgeExt = VK_BLEND_OP_LINEARDODGE_EXT,
        LinearburnExt = VK_BLEND_OP_LINEARBURN_EXT,
        VividlightExt = VK_BLEND_OP_VIVIDLIGHT_EXT,
        LinearlightExt = VK_BLEND_OP_LINEARLIGHT_EXT,
        PinlightExt = VK_BLEND_OP_PINLIGHT_EXT,
        HardmixExt = VK_BLEND_OP_HARDMIX_EXT,
        HslHueExt = VK_BLEND_OP_HSL_HUE_EXT,
        HslSaturationExt = VK_BLEND_OP_HSL_SATURATION_EXT,
        HslColorExt = VK_BLEND_OP_HSL_COLOR_EXT,
        HslLuminosityExt = VK_BLEND_OP_HSL_LUMINOSITY_EXT,
        PlusExt = VK_BLEND_OP_PLUS_EXT,
        PlusClampedExt = VK_BLEND_OP_PLUS_CLAMPED_EXT,
        PlusClampedAlphaExt = VK_BLEND_OP_PLUS_CLAMPED_ALPHA_EXT,
        PlusDarkerExt = VK_BLEND_OP_PLUS_DARKER_EXT,
        MinusExt = VK_BLEND_OP_MINUS_EXT,
        MinusClampedExt = VK_BLEND_OP_MINUS_CLAMPED_EXT,
        ContrastExt = VK_BLEND_OP_CONTRAST_EXT,
        InvertOvgExt = VK_BLEND_OP_INVERT_OVG_EXT,
        RedExt = VK_BLEND_OP_RED_EXT,
        GreenExt = VK_BLEND_OP_GREEN_EXT,
        BlueExt = VK_BLEND_OP_BLUE_EXT
    };


    /** @brief Blend factor */
    enum class BlendFactor {
        Zero = VK_BLEND_FACTOR_ZERO,
        One = VK_BLEND_FACTOR_ONE,
        SrcColor = VK_BLEND_FACTOR_SRC_COLOR,
        OneMinusSrcColor = VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR,
        DstColor = VK_BLEND_FACTOR_DST_COLOR,
        OneMinusDstColor = VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR,
        SrcAlpha = VK_BLEND_FACTOR_SRC_ALPHA,
        OneMinusSrcAlpha = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
        DstAlpha = VK_BLEND_FACTOR_DST_ALPHA,
        OneMinusDstAlpha = VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA,
        ConstantColor = VK_BLEND_FACTOR_CONSTANT_COLOR,
        OneMinusConstantColor = VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR,
        ConstantAlpha = VK_BLEND_FACTOR_CONSTANT_ALPHA,
        OneMinusConstantAlpha = VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA,
        SrcAlphaSaturate = VK_BLEND_FACTOR_SRC_ALPHA_SATURATE,
        Src1Color = VK_BLEND_FACTOR_SRC1_COLOR,
        OneMinusSrc1Color = VK_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR,
        Src1Alpha = VK_BLEND_FACTOR_SRC1_ALPHA,
        OneMinusSrc1Alpha = VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA
    };


    /** @brief Border color */
    enum class BorderColor {
        FloatTransparentBlack = VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK,
        IntTransparentBlack = VK_BORDER_COLOR_INT_TRANSPARENT_BLACK,
        FloatOpaqueBlack = VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK,
        IntOpaqueBlack = VK_BORDER_COLOR_INT_OPAQUE_BLACK,
        FloatOpaqueWhite = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE,
        IntOpaqueWhite = VK_BORDER_COLOR_INT_OPAQUE_WHITE,
        FloatCustomExt = VK_BORDER_COLOR_FLOAT_CUSTOM_EXT,
        IntCustomExt = VK_BORDER_COLOR_INT_CUSTOM_EXT
    };


    /** @brief Primitive rendering topologies */
    enum class PrimitiveTopology {
        PointList = VK_PRIMITIVE_TOPOLOGY_POINT_LIST,
        LineList = VK_PRIMITIVE_TOPOLOGY_LINE_LIST,
        LineStrip = VK_PRIMITIVE_TOPOLOGY_LINE_STRIP,
        TriangleList = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
        TriangleStrip = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP,
        TriangleFan = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN,
        LineListWithAdjacency = VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY,
        LineStripWithAdjacency = VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY,
        TriangleListWithAdjacency = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY,
        TriangleStripWithAdjacency = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY,
        PatchList = VK_PRIMITIVE_TOPOLOGY_PATCH_LIST
    };

    /** @brief Polygon modes */
    enum class PolygonMode {
        Fill = VK_POLYGON_MODE_FILL,
        Line = VK_POLYGON_MODE_LINE,
        Point = VK_POLYGON_MODE_POINT,
        FillRectangleNv = VK_POLYGON_MODE_FILL_RECTANGLE_NV
    };

    /** @brief Front face */
    enum class FrontFace {
        CounterClockwise = VK_FRONT_FACE_COUNTER_CLOCKWISE,
        Clockwise = VK_FRONT_FACE_CLOCKWISE
    };


    /** @brief Dynamic states */
    enum class DynamicState {
        Viewport = VK_DYNAMIC_STATE_VIEWPORT,
        Scissor = VK_DYNAMIC_STATE_SCISSOR,
        LineWidth = VK_DYNAMIC_STATE_LINE_WIDTH,
        DepthBias = VK_DYNAMIC_STATE_DEPTH_BIAS,
        BlendConstants = VK_DYNAMIC_STATE_BLEND_CONSTANTS,
        DepthBounds = VK_DYNAMIC_STATE_DEPTH_BOUNDS,
        StencilCompareMask = VK_DYNAMIC_STATE_STENCIL_COMPARE_MASK,
        StencilWriteMask = VK_DYNAMIC_STATE_STENCIL_WRITE_MASK,
        StencilReference = VK_DYNAMIC_STATE_STENCIL_REFERENCE,
        ViewportWScalingNv = VK_DYNAMIC_STATE_VIEWPORT_W_SCALING_NV,
        DiscardRectangleExt = VK_DYNAMIC_STATE_DISCARD_RECTANGLE_EXT,
        SampleLocationsExt = VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_EXT,
        ViewportShadingRatePaletteNv = VK_DYNAMIC_STATE_VIEWPORT_SHADING_RATE_PALETTE_NV,
        ViewportCoarseSampleOrderNv = VK_DYNAMIC_STATE_VIEWPORT_COARSE_SAMPLE_ORDER_NV,
        ExclusiveScissorNv = VK_DYNAMIC_STATE_EXCLUSIVE_SCISSOR_NV,
        LineStippleExt = VK_DYNAMIC_STATE_LINE_STIPPLE_EXT,
        CullModeExt = VK_DYNAMIC_STATE_CULL_MODE_EXT,
        FrontFaceExt = VK_DYNAMIC_STATE_FRONT_FACE_EXT,
        PrimitiveTopologyExt = VK_DYNAMIC_STATE_PRIMITIVE_TOPOLOGY_EXT,
        ViewportWithCountExt = VK_DYNAMIC_STATE_VIEWPORT_WITH_COUNT_EXT,
        ScissorWithCountExt = VK_DYNAMIC_STATE_SCISSOR_WITH_COUNT_EXT,
        VertexInputBindingStrideExt = VK_DYNAMIC_STATE_VERTEX_INPUT_BINDING_STRIDE_EXT,
        DepthTestEnableExt = VK_DYNAMIC_STATE_DEPTH_TEST_ENABLE_EXT,
        DepthWriteEnableExt = VK_DYNAMIC_STATE_DEPTH_WRITE_ENABLE_EXT,
        DepthCompareOpExt = VK_DYNAMIC_STATE_DEPTH_COMPARE_OP_EXT,
        DepthBoundsTestEnableExt = VK_DYNAMIC_STATE_DEPTH_BOUNDS_TEST_ENABLE_EXT,
        StencilTestEnableExt = VK_DYNAMIC_STATE_STENCIL_TEST_ENABLE_EXT,
        StencilOpExt = VK_DYNAMIC_STATE_STENCIL_OP_EXT
    };

    /** @brief All supported bytes formats */
    enum class Format {
        Undefined = VK_FORMAT_UNDEFINED,
        R4G4_UNORM_PACK8 = VK_FORMAT_R4G4_UNORM_PACK8,
        R4G4B4A4_UNORM_PACK16 = VK_FORMAT_R4G4B4A4_UNORM_PACK16,
        B4G4R4A4_UNORM_PACK16 = VK_FORMAT_B4G4R4A4_UNORM_PACK16,
        R5G6B5_UNORM_PACK16 = VK_FORMAT_R5G6B5_UNORM_PACK16,
        B5G6R5_UNORM_PACK16 = VK_FORMAT_B5G6R5_UNORM_PACK16,
        R5G5B5A1_UNORM_PACK16 = VK_FORMAT_R5G5B5A1_UNORM_PACK16,
        B5G5R5A1_UNORM_PACK16 = VK_FORMAT_B5G5R5A1_UNORM_PACK16,
        A1R5G5B5_UNORM_PACK16 = VK_FORMAT_A1R5G5B5_UNORM_PACK16,
        R8_UNORM = VK_FORMAT_R8_UNORM,
        R8_SNORM = VK_FORMAT_R8_SNORM,
        R8_USCALED = VK_FORMAT_R8_USCALED,
        R8_SSCALED = VK_FORMAT_R8_SSCALED,
        R8_UINT = VK_FORMAT_R8_UINT,
        R8_SINT = VK_FORMAT_R8_SINT,
        R8_SRGB = VK_FORMAT_R8_SRGB,
        R8G8_UNORM = VK_FORMAT_R8G8_UNORM,
        R8G8_SNORM = VK_FORMAT_R8G8_SNORM,
        R8G8_USCALED = VK_FORMAT_R8G8_USCALED,
        R8G8_SSCALED = VK_FORMAT_R8G8_SSCALED,
        R8G8_UINT = VK_FORMAT_R8G8_UINT,
        R8G8_SINT = VK_FORMAT_R8G8_SINT,
        R8G8_SRGB = VK_FORMAT_R8G8_SRGB,
        R8G8B8_UNORM = VK_FORMAT_R8G8B8_UNORM,
        R8G8B8_SNORM = VK_FORMAT_R8G8B8_SNORM,
        R8G8B8_USCALED = VK_FORMAT_R8G8B8_USCALED,
        R8G8B8_SSCALED = VK_FORMAT_R8G8B8_SSCALED,
        R8G8B8_UINT = VK_FORMAT_R8G8B8_UINT,
        R8G8B8_SINT = VK_FORMAT_R8G8B8_SINT,
        R8G8B8_SRGB = VK_FORMAT_R8G8B8_SRGB,
        B8G8R8_UNORM = VK_FORMAT_B8G8R8_UNORM,
        B8G8R8_SNORM = VK_FORMAT_B8G8R8_SNORM,
        B8G8R8_USCALED = VK_FORMAT_B8G8R8_USCALED,
        B8G8R8_SSCALED = VK_FORMAT_B8G8R8_SSCALED,
        B8G8R8_UINT = VK_FORMAT_B8G8R8_UINT,
        B8G8R8_SINT = VK_FORMAT_B8G8R8_SINT,
        B8G8R8_SRGB = VK_FORMAT_B8G8R8_SRGB,
        R8G8B8A8_UNORM = VK_FORMAT_R8G8B8A8_UNORM,
        R8G8B8A8_SNORM = VK_FORMAT_R8G8B8A8_SNORM,
        R8G8B8A8_USCALED = VK_FORMAT_R8G8B8A8_USCALED,
        R8G8B8A8_SSCALED = VK_FORMAT_R8G8B8A8_SSCALED,
        R8G8B8A8_UINT = VK_FORMAT_R8G8B8A8_UINT,
        R8G8B8A8_SINT = VK_FORMAT_R8G8B8A8_SINT,
        R8G8B8A8_SRGB = VK_FORMAT_R8G8B8A8_SRGB,
        B8G8R8A8_UNORM = VK_FORMAT_B8G8R8A8_UNORM,
        B8G8R8A8_SNORM = VK_FORMAT_B8G8R8A8_SNORM,
        B8G8R8A8_USCALED = VK_FORMAT_B8G8R8A8_USCALED,
        B8G8R8A8_SSCALED = VK_FORMAT_B8G8R8A8_SSCALED,
        B8G8R8A8_UINT = VK_FORMAT_B8G8R8A8_UINT,
        B8G8R8A8_SINT = VK_FORMAT_B8G8R8A8_SINT,
        B8G8R8A8_SRGB = VK_FORMAT_B8G8R8A8_SRGB,
        A8B8G8R8_UNORM_PACK32 = VK_FORMAT_A8B8G8R8_UNORM_PACK32,
        A8B8G8R8_SNORM_PACK32 = VK_FORMAT_A8B8G8R8_SNORM_PACK32,
        A8B8G8R8_USCALED_PACK32 = VK_FORMAT_A8B8G8R8_USCALED_PACK32,
        A8B8G8R8_SSCALED_PACK32 = VK_FORMAT_A8B8G8R8_SSCALED_PACK32,
        A8B8G8R8_UINT_PACK32 = VK_FORMAT_A8B8G8R8_UINT_PACK32,
        A8B8G8R8_SINT_PACK32 = VK_FORMAT_A8B8G8R8_SINT_PACK32,
        A8B8G8R8_SRGB_PACK32 = VK_FORMAT_A8B8G8R8_SRGB_PACK32,
        A2R10G10B10_UNORM_PACK32 = VK_FORMAT_A2R10G10B10_UNORM_PACK32,
        A2R10G10B10_SNORM_PACK32 = VK_FORMAT_A2R10G10B10_SNORM_PACK32,
        A2R10G10B10_USCALED_PACK32 = VK_FORMAT_A2R10G10B10_USCALED_PACK32,
        A2R10G10B10_SSCALED_PACK32 = VK_FORMAT_A2R10G10B10_SSCALED_PACK32,
        A2R10G10B10_UINT_PACK32 = VK_FORMAT_A2R10G10B10_UINT_PACK32,
        A2R10G10B10_SINT_PACK32 = VK_FORMAT_A2R10G10B10_SINT_PACK32,
        A2B10G10R10_UNORM_PACK32 = VK_FORMAT_A2B10G10R10_UNORM_PACK32,
        A2B10G10R10_SNORM_PACK32 = VK_FORMAT_A2B10G10R10_SNORM_PACK32,
        A2B10G10R10_USCALED_PACK32 = VK_FORMAT_A2B10G10R10_USCALED_PACK32,
        A2B10G10R10_SSCALED_PACK32 = VK_FORMAT_A2B10G10R10_SSCALED_PACK32,
        A2B10G10R10_UINT_PACK32 = VK_FORMAT_A2B10G10R10_UINT_PACK32,
        A2B10G10R10_SINT_PACK32 = VK_FORMAT_A2B10G10R10_SINT_PACK32,
        R16_UNORM = VK_FORMAT_R16_UNORM,
        R16_SNORM = VK_FORMAT_R16_SNORM,
        R16_USCALED = VK_FORMAT_R16_USCALED,
        R16_SSCALED = VK_FORMAT_R16_SSCALED,
        R16_UINT = VK_FORMAT_R16_UINT,
        R16_SINT = VK_FORMAT_R16_SINT,
        R16_SFLOAT = VK_FORMAT_R16_SFLOAT,
        R16G16_UNORM = VK_FORMAT_R16G16_UNORM,
        R16G16_SNORM = VK_FORMAT_R16G16_SNORM,
        R16G16_USCALED = VK_FORMAT_R16G16_USCALED,
        R16G16_SSCALED = VK_FORMAT_R16G16_SSCALED,
        R16G16_UINT = VK_FORMAT_R16G16_UINT,
        R16G16_SINT = VK_FORMAT_R16G16_SINT,
        R16G16_SFLOAT = VK_FORMAT_R16G16_SFLOAT,
        R16G16B16_UNORM = VK_FORMAT_R16G16B16_UNORM,
        R16G16B16_SNORM = VK_FORMAT_R16G16B16_SNORM,
        R16G16B16_USCALED = VK_FORMAT_R16G16B16_USCALED,
        R16G16B16_SSCALED = VK_FORMAT_R16G16B16_SSCALED,
        R16G16B16_UINT = VK_FORMAT_R16G16B16_UINT,
        R16G16B16_SINT = VK_FORMAT_R16G16B16_SINT,
        R16G16B16_SFLOAT = VK_FORMAT_R16G16B16_SFLOAT,
        R16G16B16A16_UNORM = VK_FORMAT_R16G16B16A16_UNORM,
        R16G16B16A16_SNORM = VK_FORMAT_R16G16B16A16_SNORM,
        R16G16B16A16_USCALED = VK_FORMAT_R16G16B16A16_USCALED,
        R16G16B16A16_SSCALED = VK_FORMAT_R16G16B16A16_SSCALED,
        R16G16B16A16_UINT = VK_FORMAT_R16G16B16A16_UINT,
        R16G16B16A16_SINT = VK_FORMAT_R16G16B16A16_SINT,
        R16G16B16A16_SFLOAT = VK_FORMAT_R16G16B16A16_SFLOAT,
        R32_UINT = VK_FORMAT_R32_UINT,
        R32_SINT = VK_FORMAT_R32_SINT,
        R32_SFLOAT = VK_FORMAT_R32_SFLOAT,
        R32G32_UINT = VK_FORMAT_R32G32_UINT,
        R32G32_SINT = VK_FORMAT_R32G32_SINT,
        R32G32_SFLOAT = VK_FORMAT_R32G32_SFLOAT,
        R32G32B32_UINT = VK_FORMAT_R32G32B32_UINT,
        R32G32B32_SINT = VK_FORMAT_R32G32B32_SINT,
        R32G32B32_SFLOAT = VK_FORMAT_R32G32B32_SFLOAT,
        R32G32B32A32_UINT = VK_FORMAT_R32G32B32A32_UINT,
        R32G32B32A32_SINT = VK_FORMAT_R32G32B32A32_SINT,
        R32G32B32A32_SFLOAT = VK_FORMAT_R32G32B32A32_SFLOAT,
        R64_UINT = VK_FORMAT_R64_UINT,
        R64_SINT = VK_FORMAT_R64_SINT,
        R64_SFLOAT = VK_FORMAT_R64_SFLOAT,
        R64G64_UINT = VK_FORMAT_R64G64_UINT,
        R64G64_SINT = VK_FORMAT_R64G64_SINT,
        R64G64_SFLOAT = VK_FORMAT_R64G64_SFLOAT,
        R64G64B64_UINT = VK_FORMAT_R64G64B64_UINT,
        R64G64B64_SINT = VK_FORMAT_R64G64B64_SINT,
        R64G64B64_SFLOAT = VK_FORMAT_R64G64B64_SFLOAT,
        R64G64B64A64_UINT = VK_FORMAT_R64G64B64A64_UINT,
        R64G64B64A64_SINT = VK_FORMAT_R64G64B64A64_SINT,
        R64G64B64A64_SFLOAT = VK_FORMAT_R64G64B64A64_SFLOAT,
        B10G11R11_UFLOAT_PACK32 = VK_FORMAT_B10G11R11_UFLOAT_PACK32,
        E5B9G9R9_UFLOAT_PACK32 = VK_FORMAT_E5B9G9R9_UFLOAT_PACK32,
        D16_UNORM = VK_FORMAT_D16_UNORM,
        X8_D24_UNORM_PACK32 = VK_FORMAT_X8_D24_UNORM_PACK32,
        D32_SFLOAT = VK_FORMAT_D32_SFLOAT,
        S8_UINT = VK_FORMAT_S8_UINT,
        D16_UNORM_S8_UINT = VK_FORMAT_D16_UNORM_S8_UINT,
        D24_UNORM_S8_UINT = VK_FORMAT_D24_UNORM_S8_UINT,
        D32_SFLOAT_S8_UINT = VK_FORMAT_D32_SFLOAT_S8_UINT,
        BC1_RGB_UNORM_BLOCK = VK_FORMAT_BC1_RGB_UNORM_BLOCK,
        BC1_RGB_SRGB_BLOCK = VK_FORMAT_BC1_RGB_SRGB_BLOCK,
        BC1_RGBA_UNORM_BLOCK = VK_FORMAT_BC1_RGBA_UNORM_BLOCK,
        BC1_RGBA_SRGB_BLOCK = VK_FORMAT_BC1_RGBA_SRGB_BLOCK,
        BC2_UNORM_BLOCK = VK_FORMAT_BC2_UNORM_BLOCK,
        BC2_SRGB_BLOCK = VK_FORMAT_BC2_SRGB_BLOCK,
        BC3_UNORM_BLOCK = VK_FORMAT_BC3_UNORM_BLOCK,
        BC3_SRGB_BLOCK = VK_FORMAT_BC3_SRGB_BLOCK,
        BC4_UNORM_BLOCK = VK_FORMAT_BC4_UNORM_BLOCK,
        BC4_SNORM_BLOCK = VK_FORMAT_BC4_SNORM_BLOCK,
        BC5_UNORM_BLOCK = VK_FORMAT_BC5_UNORM_BLOCK,
        BC5_SNORM_BLOCK = VK_FORMAT_BC5_SNORM_BLOCK,
        BC6H_UFLOAT_BLOCK = VK_FORMAT_BC6H_UFLOAT_BLOCK,
        BC6H_SFLOAT_BLOCK = VK_FORMAT_BC6H_SFLOAT_BLOCK,
        BC7_UNORM_BLOCK = VK_FORMAT_BC7_UNORM_BLOCK,
        BC7_SRGB_BLOCK = VK_FORMAT_BC7_SRGB_BLOCK,
        ETC2_R8G8B8_UNORM_BLOCK = VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK,
        ETC2_R8G8B8_SRGB_BLOCK = VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK,
        ETC2_R8G8B8A1_UNORM_BLOCK = VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK,
        ETC2_R8G8B8A1_SRGB_BLOCK = VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK,
        ETC2_R8G8B8A8_UNORM_BLOCK = VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK,
        ETC2_R8G8B8A8_SRGB_BLOCK = VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK,
        EAC_R11_UNORM_BLOCK = VK_FORMAT_EAC_R11_UNORM_BLOCK,
        EAC_R11_SNORM_BLOCK = VK_FORMAT_EAC_R11_SNORM_BLOCK,
        EAC_R11G11_UNORM_BLOCK = VK_FORMAT_EAC_R11G11_UNORM_BLOCK,
        EAC_R11G11_SNORM_BLOCK = VK_FORMAT_EAC_R11G11_SNORM_BLOCK,
        ASTC_4x4_UNORM_BLOCK = VK_FORMAT_ASTC_4x4_UNORM_BLOCK,
        ASTC_4x4_SRGB_BLOCK = VK_FORMAT_ASTC_4x4_SRGB_BLOCK,
        ASTC_5x4_UNORM_BLOCK = VK_FORMAT_ASTC_5x4_UNORM_BLOCK,
        ASTC_5x4_SRGB_BLOCK = VK_FORMAT_ASTC_5x4_SRGB_BLOCK,
        ASTC_5x5_UNORM_BLOCK = VK_FORMAT_ASTC_5x5_UNORM_BLOCK,
        ASTC_5x5_SRGB_BLOCK = VK_FORMAT_ASTC_5x5_SRGB_BLOCK,
        ASTC_6x5_UNORM_BLOCK = VK_FORMAT_ASTC_6x5_UNORM_BLOCK,
        ASTC_6x5_SRGB_BLOCK = VK_FORMAT_ASTC_6x5_SRGB_BLOCK,
        ASTC_6x6_UNORM_BLOCK = VK_FORMAT_ASTC_6x6_UNORM_BLOCK,
        ASTC_6x6_SRGB_BLOCK = VK_FORMAT_ASTC_6x6_SRGB_BLOCK,
        ASTC_8x5_UNORM_BLOCK = VK_FORMAT_ASTC_8x5_UNORM_BLOCK,
        ASTC_8x5_SRGB_BLOCK = VK_FORMAT_ASTC_8x5_SRGB_BLOCK,
        ASTC_8x6_UNORM_BLOCK = VK_FORMAT_ASTC_8x6_UNORM_BLOCK,
        ASTC_8x6_SRGB_BLOCK = VK_FORMAT_ASTC_8x6_SRGB_BLOCK,
        ASTC_8x8_UNORM_BLOCK = VK_FORMAT_ASTC_8x8_UNORM_BLOCK,
        ASTC_8x8_SRGB_BLOCK = VK_FORMAT_ASTC_8x8_SRGB_BLOCK,
        ASTC_10x5_UNORM_BLOCK = VK_FORMAT_ASTC_10x5_UNORM_BLOCK,
        ASTC_10x5_SRGB_BLOCK = VK_FORMAT_ASTC_10x5_SRGB_BLOCK,
        ASTC_10x6_UNORM_BLOCK = VK_FORMAT_ASTC_10x6_UNORM_BLOCK,
        ASTC_10x6_SRGB_BLOCK = VK_FORMAT_ASTC_10x6_SRGB_BLOCK,
        ASTC_10x8_UNORM_BLOCK = VK_FORMAT_ASTC_10x8_UNORM_BLOCK,
        ASTC_10x8_SRGB_BLOCK = VK_FORMAT_ASTC_10x8_SRGB_BLOCK,
        ASTC_10x10_UNORM_BLOCK = VK_FORMAT_ASTC_10x10_UNORM_BLOCK,
        ASTC_10x10_SRGB_BLOCK = VK_FORMAT_ASTC_10x10_SRGB_BLOCK,
        ASTC_12x10_UNORM_BLOCK = VK_FORMAT_ASTC_12x10_UNORM_BLOCK,
        ASTC_12x10_SRGB_BLOCK = VK_FORMAT_ASTC_12x10_SRGB_BLOCK,
        ASTC_12x12_UNORM_BLOCK = VK_FORMAT_ASTC_12x12_UNORM_BLOCK,
        ASTC_12x12_SRGB_BLOCK = VK_FORMAT_ASTC_12x12_SRGB_BLOCK,
        G8B8G8R8_422_UNORM = VK_FORMAT_G8B8G8R8_422_UNORM,
        B8G8R8G8_422_UNORM = VK_FORMAT_B8G8R8G8_422_UNORM,
        G8_B8_R8_3PLANE_420_UNORM = VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM,
        G8_B8R8_2PLANE_420_UNORM = VK_FORMAT_G8_B8R8_2PLANE_420_UNORM,
        G8_B8_R8_3PLANE_422_UNORM = VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM,
        G8_B8R8_2PLANE_422_UNORM = VK_FORMAT_G8_B8R8_2PLANE_422_UNORM,
        G8_B8_R8_3PLANE_444_UNORM = VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM,
        R10X6_UNORM_PACK16 = VK_FORMAT_R10X6_UNORM_PACK16,
        R10X6G10X6_UNORM_2PACK16 = VK_FORMAT_R10X6G10X6_UNORM_2PACK16,
        R10X6G10X6B10X6A10X6_UNORM_4PACK16 = VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16,
        G10X6B10X6G10X6R10X6_422_UNORM_4PACK16 = VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16,
        B10X6G10X6R10X6G10X6_422_UNORM_4PACK16 = VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16,
        G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16 = VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16,
        G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16 = VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16,
        G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16 = VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16,
        G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16 = VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16,
        G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16 = VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16,
        R12X4_UNORM_PACK16 = VK_FORMAT_R12X4_UNORM_PACK16,
        R12X4G12X4_UNORM_2PACK16 = VK_FORMAT_R12X4G12X4_UNORM_2PACK16,
        R12X4G12X4B12X4A12X4_UNORM_4PACK16 = VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16,
        G12X4B12X4G12X4R12X4_422_UNORM_4PACK16 = VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16,
        B12X4G12X4R12X4G12X4_422_UNORM_4PACK16 = VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16,
        G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16 = VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16,
        G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16 = VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16,
        G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16 = VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16,
        G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16 = VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16,
        G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16 = VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16,
        G16B16G16R16_422_UNORM = VK_FORMAT_G16B16G16R16_422_UNORM,
        B16G16R16G16_422_UNORM = VK_FORMAT_B16G16R16G16_422_UNORM,
        G16_B16_R16_3PLANE_420_UNORM = VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM,
        G16_B16R16_2PLANE_420_UNORM = VK_FORMAT_G16_B16R16_2PLANE_420_UNORM,
        G16_B16_R16_3PLANE_422_UNORM = VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM,
        G16_B16R16_2PLANE_422_UNORM = VK_FORMAT_G16_B16R16_2PLANE_422_UNORM,
        G16_B16_R16_3PLANE_444_UNORM = VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM,
        PVRTC1_2BPP_UNORM_BLOCK_IMG = VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG,
        PVRTC1_4BPP_UNORM_BLOCK_IMG = VK_FORMAT_PVRTC1_4BPP_UNORM_BLOCK_IMG,
        PVRTC2_2BPP_UNORM_BLOCK_IMG = VK_FORMAT_PVRTC2_2BPP_UNORM_BLOCK_IMG,
        PVRTC2_4BPP_UNORM_BLOCK_IMG = VK_FORMAT_PVRTC2_4BPP_UNORM_BLOCK_IMG,
        PVRTC1_2BPP_SRGB_BLOCK_IMG = VK_FORMAT_PVRTC1_2BPP_SRGB_BLOCK_IMG,
        PVRTC1_4BPP_SRGB_BLOCK_IMG = VK_FORMAT_PVRTC1_4BPP_SRGB_BLOCK_IMG,
        PVRTC2_2BPP_SRGB_BLOCK_IMG = VK_FORMAT_PVRTC2_2BPP_SRGB_BLOCK_IMG,
        PVRTC2_4BPP_SRGB_BLOCK_IMG = VK_FORMAT_PVRTC2_4BPP_SRGB_BLOCK_IMG,
        ASTC_4x4_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_4x4_SFLOAT_BLOCK_EXT,
        ASTC_5x4_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_5x4_SFLOAT_BLOCK_EXT,
        ASTC_5x5_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_5x5_SFLOAT_BLOCK_EXT,
        ASTC_6x5_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_6x5_SFLOAT_BLOCK_EXT,
        ASTC_6x6_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_6x6_SFLOAT_BLOCK_EXT,
        ASTC_8x5_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_8x5_SFLOAT_BLOCK_EXT,
        ASTC_8x6_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_8x6_SFLOAT_BLOCK_EXT,
        ASTC_8x8_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_8x8_SFLOAT_BLOCK_EXT,
        ASTC_10x5_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_10x5_SFLOAT_BLOCK_EXT,
        ASTC_10x6_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_10x6_SFLOAT_BLOCK_EXT,
        ASTC_10x8_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_10x8_SFLOAT_BLOCK_EXT,
        ASTC_10x10_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_10x10_SFLOAT_BLOCK_EXT,
        ASTC_12x10_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_12x10_SFLOAT_BLOCK_EXT,
        ASTC_12x12_SFLOAT_BLOCK_EXT = VK_FORMAT_ASTC_12x12_SFLOAT_BLOCK_EXT,
        A4R4G4B4_UNORM_PACK16_EXT = VK_FORMAT_A4R4G4B4_UNORM_PACK16_EXT,
        A4B4G4R4_UNORM_PACK16_EXT = VK_FORMAT_A4B4G4R4_UNORM_PACK16_EXT,
        G8B8G8R8_422_UNORM_KHR = VK_FORMAT_G8B8G8R8_422_UNORM_KHR,
        B8G8R8G8_422_UNORM_KHR = VK_FORMAT_B8G8R8G8_422_UNORM_KHR,
        G8_B8_R8_3PLANE_420_UNORM_KHR = VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM_KHR,
        G8_B8R8_2PLANE_420_UNORM_KHR = VK_FORMAT_G8_B8R8_2PLANE_420_UNORM_KHR,
        G8_B8_R8_3PLANE_422_UNORM_KHR = VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM_KHR,
        G8_B8R8_2PLANE_422_UNORM_KHR = VK_FORMAT_G8_B8R8_2PLANE_422_UNORM_KHR,
        G8_B8_R8_3PLANE_444_UNORM_KHR = VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM_KHR,
        R10X6_UNORM_PACK16_KHR = VK_FORMAT_R10X6_UNORM_PACK16_KHR,
        R10X6G10X6_UNORM_2PACK16_KHR = VK_FORMAT_R10X6G10X6_UNORM_2PACK16_KHR,
        R10X6G10X6B10X6A10X6_UNORM_4PACK16_KHR = VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16_KHR,
        G10X6B10X6G10X6R10X6_422_UNORM_4PACK16_KHR = VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16_KHR,
        B10X6G10X6R10X6G10X6_422_UNORM_4PACK16_KHR = VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16_KHR,
        G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16_KHR = VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16_KHR,
        G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16_KHR = VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16_KHR,
        G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16_KHR = VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16_KHR,
        G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16_KHR = VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16_KHR,
        G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16_KHR = VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16_KHR,
        R12X4_UNORM_PACK16_KHR = VK_FORMAT_R12X4_UNORM_PACK16_KHR,
        R12X4G12X4_UNORM_2PACK16_KHR = VK_FORMAT_R12X4G12X4_UNORM_2PACK16_KHR,
        R12X4G12X4B12X4A12X4_UNORM_4PACK16_KHR = VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16_KHR,
        G12X4B12X4G12X4R12X4_422_UNORM_4PACK16_KHR = VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16_KHR,
        B12X4G12X4R12X4G12X4_422_UNORM_4PACK16_KHR = VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16_KHR,
        G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16_KHR = VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16_KHR,
        G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16_KHR = VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16_KHR,
        G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16_KHR = VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16_KHR,
        G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16_KHR = VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16_KHR,
        G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16_KHR = VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16_KHR,
        G16B16G16R16_422_UNORM_KHR = VK_FORMAT_G16B16G16R16_422_UNORM_KHR,
        B16G16R16G16_422_UNORM_KHR = VK_FORMAT_B16G16R16G16_422_UNORM_KHR,
        G16_B16_R16_3PLANE_420_UNORM_KHR = VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM_KHR,
        G16_B16R16_2PLANE_420_UNORM_KHR = VK_FORMAT_G16_B16R16_2PLANE_420_UNORM_KHR,
        G16_B16_R16_3PLANE_422_UNORM_KHR = VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM_KHR,
        G16_B16R16_2PLANE_422_UNORM_KHR = VK_FORMAT_G16_B16R16_2PLANE_422_UNORM_KHR,
        G16_B16_R16_3PLANE_444_UNORM_KHR = VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM_KHR
    };
}
