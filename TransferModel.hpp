/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Render instruction model
 */

#pragma once

#include "Buffer.hpp"

namespace kF::Graphics
{
    struct TransferModel;
}

/** @brief Describes a transfer command */
struct kF::Graphics::TransferModel
{
    DeviceBuffer source { VK_NULL_HANDLE }; // Source buffer
    DeviceBuffer destination { VK_NULL_HANDLE }; // Destination buffer
    BufferSize size { 0u }; // Number of bytes to transfer
    BufferOffset sourceOffset { 0u }; // Offset in source buffer
    BufferOffset destinationOffset { 0u }; // Offset in destionation buffer
};

static_assert(sizeof(kF::Graphics::TransferModel) == 40, "Transfer must take 40 bytes");