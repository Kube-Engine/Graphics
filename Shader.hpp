/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Shader
 */

#pragma once

#include <vector>

#include "VulkanHandler.hpp"

namespace kF::Graphics
{
    class Shader;
    struct ShaderModel;
    using ShaderModels = std::vector<ShaderModel>;

    enum class ShaderType {
        Vertex = VK_SHADER_STAGE_VERTEX_BIT,
        TessellationControl = VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT,
        TessellationEvaluation = VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT,
        Geometry = VK_SHADER_STAGE_GEOMETRY_BIT,
        Fragment = VK_SHADER_STAGE_FRAGMENT_BIT,
        Compute = VK_SHADER_STAGE_COMPUTE_BIT,
        AllGraphics = VK_SHADER_STAGE_ALL_GRAPHICS,
        All = VK_SHADER_STAGE_ALL,
        Raygen = VK_SHADER_STAGE_RAYGEN_BIT_NV,
        AnyHit = VK_SHADER_STAGE_ANY_HIT_BIT_NV,
        ClosestHit = VK_SHADER_STAGE_CLOSEST_HIT_BIT_NV,
        Miss = VK_SHADER_STAGE_MISS_BIT_NV,
        Intersection = VK_SHADER_STAGE_INTERSECTION_BIT_NV,
        Callable = VK_SHADER_STAGE_CALLABLE_BIT_NV,
        Task = VK_SHADER_STAGE_TASK_BIT_NV,
        Mesh = VK_SHADER_STAGE_MESH_BIT_NV
    };
}

/** @brief Describe a shader to load */
struct kF::Graphics::ShaderModel
{
    ShaderType type;
    std::string path;
};

/** @brief Abstraction of a GPU shader */
class kF::Graphics::Shader final : public VulkanHandler<VkShaderModule>
{
public:
    /** @brief A vector containing binary data */
    using BinaryCode = std::vector<std::uint32_t>;

    /** @brief Construct a shader from a path */
    Shader(Renderer &renderer, const std::string &path);

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