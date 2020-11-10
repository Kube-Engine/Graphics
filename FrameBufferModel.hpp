/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: FrameBuffer instruction model
 */

#pragma once

#include <Kube/Core/Vector.hpp>

#include "ImageView.hpp"

namespace kF::Graphics
{
    struct FrameBufferModel;
}

/** @brief Model describing a memory layout of a pipeline */
struct alignas_half_cacheline kF::Graphics::FrameBufferModel
{
    Core::TinyVector<ImageViewHandle> imageViews {};
    std::uint32_t layerCount { 1u };
};

static_assert_fit_half_cacheline(kF::Graphics::FrameBufferModel);
