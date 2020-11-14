/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: CommandRecording
 */

#pragma once

#include "Vulkan.hpp"

namespace kF::Graphics::Record
{
    /** @brief Begin / end a render pass */
    constexpr auto BeginRenderPass = ::vkCmdBeginRenderPass;
    constexpr auto EndRenderPass = ::vkCmdEndRenderPass;
}