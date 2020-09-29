/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Instance
 */

#pragma once

#include <vector>

#include <Kube/Core/Version.hpp>

#include "VulkanHandler.hpp"
#include "BackendWindow.hpp"

namespace kF { class Instance; }

class kF::Instance final : public VulkanHandler<VkInstance>
{
public:
    using Extensions = std::vector<const char *>;
    using Layers = std::vector<const char *>;

    Instance(Renderer &renderer, const Version applicationVersion);
    Instance(Instance &&other) = default;
    ~Instance(void);

    Instance &operator=(Instance &&other) = default;

private:
    void createInstance(const Version applicationVersion);

    [[nodiscard]] Layers getLayers(void) const;
    [[nodiscard]] Extensions getExtensions(BackendWindow *window) const;
};
