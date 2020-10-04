/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Instance
 */

#pragma once

#include <vector>

#include <Kube/Core/Version.hpp>

#include "VulkanHandler.hpp"
#include "BackendWindow.hpp"

namespace kF::Graphics
{
    class Instance;
}

/** @brief Abstraction of the low-level API instance */
class kF::Graphics::Instance final : public VulkanHandler<VkInstance>
{
public:
    /** @brief Instance extension list */
    using Extensions = std::vector<const char *>;

    /** @brief Debug layers list */
    using Layers = std::vector<const char *>;

    /** @brief Construct an instance */
    Instance(Renderer &renderer, const Version applicationVersion);

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
