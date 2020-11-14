/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: SubmitInfo
 */

#pragma once

#include <Kube/Core/Assert.hpp>

#include "Vulkan.hpp"

namespace kF::Graphics
{
    struct SubmitInfo;
};

/** @brief Describe how to create a sampler */
struct kF::Graphics::SubmitInfo : public VkSubmitInfo
{
    /** @brief Initialize constructor */
    SubmitInfo(const CommandHandle * const commandBegin, const CommandHandle * const commandEnd,
            const SemaphoreHandle * const waitBegin, const SemaphoreHandle * const waitEnd,
            const PipelineStageFlags * const waitStagesBegin, const PipelineStageFlags * const waitStagesEnd,
            const SemaphoreHandle * const signalBegin, const SemaphoreHandle * const signalEnd)
        noexcept_ndebug
        : VkSubmitInfo {
            sType: VK_STRUCTURE_TYPE_SUBMIT_INFO,
            pNext: nullptr,
            waitSemaphoreCount: static_cast<std::uint32_t>(std::distance(waitBegin, waitEnd)),
            pWaitSemaphores: waitBegin,
            pWaitDstStageMask: reinterpret_cast<const VkPipelineStageFlags * const>(waitStagesBegin),
            commandBufferCount: static_cast<std::uint32_t>(std::distance(commandBegin, commandEnd)),
            pCommandBuffers: commandBegin,
            signalSemaphoreCount: static_cast<std::uint32_t>(std::distance(signalBegin, signalEnd)),
            pSignalSemaphores: signalBegin,
        }
    {
        kFAssert(std::distance(waitBegin, waitEnd) == std::distance(waitStagesBegin, waitStagesEnd),
            throw std::logic_error("Graphics::SubmitInfo::SubmitInfo: Mismatching count of wait semaphore and wait pipeline stages"));
    }

    /** @brief POD semantics */
    SubmitInfo(const SubmitInfo &other) noexcept = default;
    SubmitInfo(SubmitInfo &&other) noexcept = default;
    SubmitInfo &operator=(const SubmitInfo &other) noexcept = default;
    SubmitInfo &operator=(SubmitInfo &&other) noexcept = default;
};
