/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: PhysicalDevice
 */

#include <stdexcept>
#include <iostream>

#include <Kube/Core/Core.hpp>

#include "Renderer.hpp"

using namespace kF;
using namespace kF::Literal;

PhysicalDevice::PhysicalDevice(Renderer &renderer)
    : VulkanHandler<VkPhysicalDevice>(renderer)
{
    auto devices = getDevices();

    selectDevice(devices);
#ifndef KUBE_NO_DEBUG
    std::cout << "Devices:" << std::endl;
    for (auto &device : devices) {
        VkPhysicalDeviceProperties properties;
        vkGetPhysicalDeviceProperties(device, &properties);
        std::cout << (device == handle() ? "\t-> " : "\t") << properties.deviceName << std::endl;
    }
#endif
}

PhysicalDevice::~PhysicalDevice(void)
{
}

PhysicalDevice::Devices PhysicalDevice::getDevices(void) const
{
    std::vector<VkPhysicalDevice> devices;

    if (auto res = FillVkContainer(devices, &::vkEnumeratePhysicalDevices, parent().getInstance()); res != VK_SUCCESS)
        throw std::runtime_error("PhysicalDevice::PhysicalDevice: Couldn't enumerate physical devices '"_str + ErrorMessage(res) + '\'');
    return devices;
}

void PhysicalDevice::selectDevice(const Devices &devices)
{
    if (devices.empty())
        throw std::runtime_error("PhysicalDevice::selectDevice: No device detected !");
    handle() = devices[0];
}