/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: LogicalDevice
 */

#pragma once

#include <vector>

#include "VulkanHandler.hpp"

namespace kF { class LogicalDevice; }

class kF::LogicalDevice final : public VulkanHandler<VkDevice>
{
public:
    using Extensions = std::vector<const char *>;

    LogicalDevice(Renderer &renderer);
    LogicalDevice(LogicalDevice &&other) = default;
    ~LogicalDevice(void);

    LogicalDevice &operator=(LogicalDevice &&other) = default;

private:
    void createLogicalDevice(void);

    [[nodiscard]] Extensions getExtensions(void) const;
};