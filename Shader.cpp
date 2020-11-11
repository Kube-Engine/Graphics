/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Shader
 */

#include <fstream>

#include <Kube/Core/StringLiteral.hpp>

#include "Renderer.hpp"

using namespace kF;
using namespace kF::Literal;

Graphics::Shader::~Shader(void) noexcept
{
    ::vkDestroyShaderModule(parent().logicalDevice(), handle(), nullptr);
}

Graphics::Shader::BinaryCode Graphics::Shader::GetBinaryCode(const std::string &path)
{
    std::ifstream is(path, std::ios::ate | std::ios::binary);
    BinaryCode binary;

    if (!is || !is.tellg())
        throw std::runtime_error("Graphics::Renderer::GetBinaryCode: Invalid shader file '" + path + '\'');
    binary.resize(is.tellg());
    is.seekg(0);
    is.read(reinterpret_cast<char *>(binary.data()), binary.size());
    return binary;
}

void Graphics::Shader::createShaderModule(const std::string &path)
{
    auto binary = GetBinaryCode(path);
    VkShaderModuleCreateInfo shaderModuleInfo {
        sType: VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        pNext: nullptr,
        flags: VkShaderModuleCreateFlags(),
        codeSize: binary.size(),
        pCode: binary.data()
    };

    if (auto res = ::vkCreateShaderModule(parent().logicalDevice(), &shaderModuleInfo, nullptr, &handle()); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::Shader::createShaderModule: Couldn't create shader module '"s + ErrorMessage(res) + "' at path '" + path + '\'');
}