/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Render Pass
 */

#include <Kube/Core/Core.hpp>

#include "Renderer.hpp"

using namespace kF;
using namespace kF::Literal;

RenderPass::RenderPass(Renderer &renderer)
    : VulkanHandler<VkRenderPass>(renderer)
{
    createRenderPass();
}

RenderPass::~RenderPass(void)
{
    ::vkDestroyRenderPass(parent().getLogicalDevice(), handle(), nullptr);
}

void RenderPass::createRenderPass(void)
{
    VkAttachmentDescription colorAttachment {
        .flags = VkAttachmentDescriptionFlags(),
        .format = parent().getSwapchain().getSurfaceFormat().format,
        .samples = VK_SAMPLE_COUNT_1_BIT,
        .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
        .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
        .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
        .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
        .finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
    };
    VkAttachmentReference colorAttachmentRef {
        .attachment = 0,
        .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
    };
    VkSubpassDescription supbass {
        .flags = VkSubpassDescriptionFlags(),
        .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
        .inputAttachmentCount = 0,
        .pInputAttachments = nullptr,
        .colorAttachmentCount = 1,
        .pColorAttachments = &colorAttachmentRef,
        .pResolveAttachments = nullptr,
        .pDepthStencilAttachment = nullptr,
        .preserveAttachmentCount = 0,
        .pPreserveAttachments = nullptr
    };
    VkRenderPassCreateInfo renderPassInfo {
        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
        .pNext = nullptr,
        .flags = VkRenderPassCreateFlags(),
        .attachmentCount = 1,
        .pAttachments = &colorAttachment,
        .subpassCount = 1,
        .pSubpasses = &supbass,
        .dependencyCount = 0,
        .pDependencies = nullptr
    };

    if (auto res = ::vkCreateRenderPass(parent().getLogicalDevice(), &renderPassInfo, nullptr, &handle()); res != VK_SUCCESS)
        throw std::runtime_error("RenderPass::createRenderPass: Couldn't create render pass '"_str + ErrorMessage(res) + '\'');
}