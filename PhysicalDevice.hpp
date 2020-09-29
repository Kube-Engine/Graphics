/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: PhysicalDevice
 */

#pragma once

#include <vector>

#include "VulkanHandler.hpp"

namespace kF { class PhysicalDevice; }

class kF::PhysicalDevice final : public VulkanHandler<VkPhysicalDevice>
{
public:
    using Devices = std::vector<VkPhysicalDevice>;

    PhysicalDevice(Renderer &renderer);
    PhysicalDevice(PhysicalDevice &&other) = default;
    ~PhysicalDevice(void);

    PhysicalDevice &operator=(PhysicalDevice &&other) = default;

private:
    [[nodiscard]] Devices getDevices(void) const;

    void selectDevice(const Devices &devices);
};