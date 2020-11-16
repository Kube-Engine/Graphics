/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: CommandRecording
 */

#pragma once

#include "Vulkan.hpp"
#include "RenderPassBeginInfo.hpp"
#include "BufferCopy.hpp"

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
            const std::uint32_t firstVertex = 0u, const std::uint32_t firstInstance = 0) const noexcept
        { ::vkCmdDraw(_command, vertexCount, instanceCount, firstVertex, firstInstance); }

    /** @brief Indexed draw commands */
    void drawIndexed(const std::uint32_t indexCount, const std::uint32_t instanceCount,
            const std::uint32_t firstIndex, const std::int32_t vertexOffset = 0, const std::uint32_t firstInstance = 0u) const noexcept
        { ::vkCmdDrawIndexed(_command, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance); }


    /** @brief Bind a single vertex buffer */
    void bindVertexBuffer(const std::uint32_t binding, const BufferHandle buffer, const BufferSize offset = 0u) const noexcept
        { ::vkCmdBindVertexBuffers(_command, binding, 1, &buffer, &offset); }

    /** @brief Bind vertex buffers */
    void bindVertexBuffers(const std::uint32_t firstBinding, const std::uint32_t bindingCount,
            const BufferHandle * const pBuffers, const BufferSize * const pOffsets) const noexcept
        { ::vkCmdBindVertexBuffers(_command, firstBinding, bindingCount, pBuffers, pOffsets); }


    /** @brief Buffer copy command with one region */
    void copyBuffer(const BufferHandle srcBuffer, const BufferHandle dstBuffer, const BufferCopy &region) const noexcept
        { ::vkCmdCopyBuffer(_command, srcBuffer, dstBuffer, 1, &region); }

    /** @brief Buffer copy command with multiple regions */
    void copyBuffer(const BufferHandle srcBuffer, const BufferHandle dstBuffer, const BufferCopy * const regionBegin, const BufferCopy * const regionEnd) const noexcept
        { ::vkCmdCopyBuffer(_command, srcBuffer, dstBuffer, static_cast<std::uint32_t>(std::distance(regionBegin, regionEnd)), regionBegin); }

private:
    CommandHandle _command;
};