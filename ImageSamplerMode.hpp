/**
 * @ Author: Pierre Veysseyre
 * @ Description: ImageSamplerMode.hpp
 */

#pragma once

#include "Vulkan.hpp"

namespace kF::Graphics
{
    struct ImageSamplerModel;

    using BorderColor = VkBorderColor;
};

struct kF::Graphics::ImageSamplerModel
{
    enum class Interpolation : uint8_t {
        Nearest = VK_FILTER_NEAREST,
        Linear = VK_FILTER_LINEAR,
        Cubic = VK_FILTER_CUBIC_IMG
    };

    enum class BoundMode : uint8_t {
        Repeat = VK_SAMPLER_ADDRESS_MODE_REPEAT,
        RepeatMiror = VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT,
        ClampEdge = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
        ClampBorder = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER,
        ClampEdgeMiror = VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE
    };

    enum class ComparisonMode : uint8_t {
        Never = VK_COMPARE_OP_NEVER,
        Less = VK_COMPARE_OP_LESS,
        Equal = VK_COMPARE_OP_EQUAL,
        LessEqual = VK_COMPARE_OP_LESS_OR_EQUAL,
        Greater = VK_COMPARE_OP_GREATER,
        NotEqual = VK_COMPARE_OP_NOT_EQUAL,
        GreaterEqual = VK_COMPARE_OP_GREATER_OR_EQUAL,
        Always = VK_COMPARE_OP_ALWAYS
    };

    enum class MipMapMode : uint8_t {
        Nearest = VK_SAMPLER_MIPMAP_MODE_NEAREST,
        Linear = VK_SAMPLER_MIPMAP_MODE_LINEAR
    };

    Interpolation       magFilter { Interpolation::Linear };
    Interpolation       minFilter { Interpolation::Linear };

    BoundMode           boundX { BoundMode::Repeat };
    BoundMode           boundY { BoundMode::Repeat };
    BoundMode           boundZ { BoundMode::Repeat };

    bool                anisotropyEnabled {};
    float               anisotropyMax { 16.f };

    BorderColor         borderColor { VK_BORDER_COLOR_INT_OPAQUE_BLACK };
    bool                normalizedCoord = { true };

    bool                comparisonEnabled { false };
    ComparisonMode      comparisonMode { ComparisonMode::Always };

    MipMapMode          mipMapMode { MipMapMode::Linear };
    float               mipMapLodBias {};
    float               minLod {};
    float               maxLod {};
};