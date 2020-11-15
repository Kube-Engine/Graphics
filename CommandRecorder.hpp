/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: CommandRecording
 */

#pragma once

#include "Vulkan.hpp"
#include "RenderPassBeginInfo.hpp"


namespace kF::Graphics
{
    class CommandRecorder;
}

class kF::Graphics::CommandRecorder
{
public:
    /** @brief Construct the recorder out of a command (has no ownership) */
    CommandRecorder(const CommandHandle command) noexcept : _command(command) {}

    /** POD semantics */
    CommandRecorder(const CommandRecorder &other) noexcept = default;
    CommandRecorder(CommandRecorder &&other) noexcept = default;
    ~CommandRecorder(void) noexcept = default;
    CommandRecorder &operator=(const CommandRecorder &other) noexcept = default;
    CommandRecorder &operator=(CommandRecorder &&other) noexcept = default;


    /** @brief Begin a render pass */
    void beginRenderPass(const RenderPassBeginInfo &renderPassBegin, const SubpassContents contents) const noexcept
        { ::vkCmdBeginRenderPass(_command, &renderPassBegin, static_cast<VkSubpassContents>(contents)); }

    /** @brief End a render pass */
    void endRenderPass(void) const noexcept
        { ::vkCmdEndRenderPass(_command); }


    /** @brief Bind a pipeline */
    void bindPipeline(const PipelineBindPoint pipelineBindPoint, const PipelineHandle pipeline) const noexcept
        { ::vkCmdBindPipeline(_command, static_cast<VkPipelineBindPoint>(pipelineBindPoint), pipeline); }


    /** @brief Draw commands */
    void draw(const std::uint32_t vertexCount, const std::uint32_t instanceCount,
            const std::uint32_t firstVertex, const std::uint32_t firstInstance) const noexcept
        { ::vkCmdDraw(_command, vertexCount, instanceCount, firstVertex, firstInstance); }
    void drawIndexed(const std::uint32_t indexCount, const std::uint32_t instanceCount,
            const std::uint32_t firstIndex, const std::int32_t vertexOffset, const std::uint32_t firstInstance) const noexcept
        { ::vkCmdDrawIndexed(_command, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance); }

private:
    CommandHandle _command;
};