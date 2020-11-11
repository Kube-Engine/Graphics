/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Instance
 */

#pragma once

#include <vector>

#include <Kube/Core/Version.hpp>

#include "VulkanHandle.hpp"
#include "BackendWindow.hpp"

namespace kF::Graphics
{
    class Instance;
}

/** @brief Abstraction of the low-level API instance */
class kF::Graphics::Instance final : public VulkanHandle<VkInstance>
{
public:
    /** @brief Instance extension list */
    using Extensions = std::vector<const char *>;

    /** @brief Debug layers list */
    using Layers = std::vector<const char *>;

    /** @brief Construct an instance */
    Instance(Renderer &renderer, const Version applicationVersion) : VulkanHandle<VkInstance>(renderer)
        { createInstance(applicationVersion); }

    /** @brief Move constructor */
    Instance(Instance &&other) noexcept = default;

    /** @brief Destroy the instance */
    ~Instance(void) noexcept;

    /** @brief Move assignment */
    Instance &operator=(Instance &&other) noexcept = default;

private:
    /** @brief Create an instance */
    void createInstance(const Version applicationVersion);

    /** @brief Get the list of debug layers */
    [[nodiscard]] Layers getLayers(void) const;

    /** @brief Get the list of instance extensions */
    [[nodiscard]] Extensions getExtensions(BackendWindow *window) const;
};
