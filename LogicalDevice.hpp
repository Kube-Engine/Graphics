/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: LogicalDevice
 */

#pragma once

#include <vector>

#include "VulkanHandler.hpp"

namespace kF::Graphics
{
    class LogicalDevice;
}

/** @brief The logical device abstracts the communication with a physical device */
class kF::Graphics::LogicalDevice final : public VulkanHandler<VkDevice>
{
public:
    /** @brief Logical device extension list */
    using Extensions = std::vector<const char *>;

    /** @brief Create a logical device */
    LogicalDevice(Renderer &renderer);

    /** @brief Move constructor */
    LogicalDevice(LogicalDevice &&other) noexcept = default;

    /** @brief Destruct the logical device*/
    ~LogicalDevice(void) noexcept;

    /** @brief Move assignment */
    LogicalDevice &operator=(LogicalDevice &&other) noexcept = default;

private:
    /** @brief Create a logical device */
    void createLogicalDevice(void);

    /** @brief Get the supported extensions */
    [[nodiscard]] Extensions getExtensions(void) const;
};