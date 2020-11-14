/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: LogicalDevice
 */

#pragma once

#include <Kube/Core/Vector.hpp>

#include "VulkanHandle.hpp"

namespace kF::Graphics
{
    class LogicalDevice;
}

/** @brief The logical device abstracts the communication with a physical device */
class kF::Graphics::LogicalDevice final : public CachedVulkanHandle<VkDevice>
{
public:
    /** @brief Logical device extension list */
    using Extensions = Core::Vector<const char *>;

    /** @brief Create a logical device */
    LogicalDevice(void) { createLogicalDevice(); }

    /** @brief Move constructor */
    LogicalDevice(LogicalDevice &&other) noexcept = default;

    /** @brief Destruct the logical device*/
    ~LogicalDevice(void) noexcept;

    /** @brief Move assignment */
    LogicalDevice &operator=(LogicalDevice &&other) noexcept = default;


    /** @brief Wait until logical device is IDLE */
    void waitIdle(void) noexcept;

private:
    /** @brief Create a logical device */
    void createLogicalDevice(void);

    /** @brief Get the supported extensions */
    [[nodiscard]] Extensions getExtensions(void) const;
};