/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Shader
 */

#include <fstream>

#include <Kube/Core/Core.hpp>

#include "Shader.hpp"
#include "Renderer.hpp"

using namespace kF;
using namespace kF::Literal;

Shader::Shader(Renderer &renderer, const std::string &path)
    : VulkanHandler<VkShaderModule>(renderer)
{
    createShaderModule(path);
}

Shader::~Shader(void)
{
    ::vkDestroyShaderModule(parent().getLogicalDevice(), handle(), nullptr);
}

Shader::BinaryCode Shader::GetBinaryCode(const std::string &path)
{
    std::ifstream is(path, std::ios::ate | std::ios::binary);
    BinaryCode binary;

    if (!is || !is.tellg())
        throw std::runtime_error("Renderer::getShaderBinary: Invalid shader file '" + path + '\'');
    binary.resize(is.tellg());
    is.seekg(0);
    is.read(reinterpret_cast<char *>(binary.data()), binary.size());
    return binary;
}

void Shader::createShaderModule(const std::string &path)
{
    auto binary = GetBinaryCode(path);
    VkShaderModuleCreateInfo shaderModuleInfo {
        .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .pNext = nullptr,
        .flags = VkShaderModuleCreateFlags(),
        .codeSize = binary.size(),
        .pCode = binary.data()
    };

    if (auto res = ::vkCreateShaderModule(parent().getLogicalDevice(), &shaderModuleInfo, nullptr, &handle()); res != VK_SUCCESS)
        throw std::runtime_error("Shader::createShaderModule: Couldn't create shader module '"_str + ErrorMessage(res) + "' at path '" + path + '\'');
}