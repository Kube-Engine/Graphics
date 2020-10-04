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

Graphics::PhysicalDevice::PhysicalDevice(Renderer &renderer)
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

Graphics::PhysicalDevice::Devices Graphics::PhysicalDevice::getDevices(void) const
{
    Devices devices;

    if (auto res = FillVkContainer(devices, &::vkEnumeratePhysicalDevices, parent().getInstance()); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::PhysicalDevice::PhysicalDevice: Couldn't enumerate physical devices '"_str + ErrorMessage(res) + '\'');
    return devices;
}

void Graphics::PhysicalDevice::selectDevice(const Devices &devices)
{
    if (devices.empty())
        throw std::runtime_error("Graphics::PhysicalDevice::selectDevice: No device detected !");
    handle() = devices[0];
}