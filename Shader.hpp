/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Shader
 */

#pragma once

#include <Kube/Core/Vector.hpp>

#include "VulkanHandle.hpp"

namespace kF::Graphics
{
    class Shader;
}

/** @brief Abstraction of a GPU shader */
class kF::Graphics::Shader final : public VulkanHandle<VkShaderModule>
{
public:
    /** @brief A vector containing binary data */
    using BinaryCode = Core::Vector<std::uint32_t>;

    /** @brief Construct a shader from a path */
    Shader(const std::string &path) { createShaderModule(path); }

    /** @brief Move constructor */
    Shader(Shader &&other) noexcept = default;

    /** ^brief Destruct the shader */
    ~Shader(void) noexcept;

    /** @brief Move assignment */
    Shader &operator=(Shader &&other) noexcept = default;

    /** @brief Get the binary code of a shader from its path */
    [[nodiscard]] static BinaryCode GetBinaryCode(const std::string &path);

private:
    /** @brief Create a shader module from a path */
    void createShaderModule(const std::string &path);
};