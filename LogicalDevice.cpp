/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: LogicalDevice
 */

#include <stdexcept>
#include <cstring>
#include <algorithm>
#include <iostream>

#include <Kube/Core/Core.hpp>

#include "Renderer.hpp"

using namespace kF;
using namespace kF::Literal;

LogicalDevice::LogicalDevice(Renderer &renderer)
    : VulkanHandler<VkDevice>(renderer)
{
    createLogicalDevice();
}

LogicalDevice::~LogicalDevice(void)
{
    ::vkDestroyDevice(handle(), nullptr);
}

void LogicalDevice::createLogicalDevice(void)
{
    auto extensions = getExtensions();
    auto queueInfos = parent().getQueueHandler().registerQueues();
    VkDeviceCreateInfo deviceInfo {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .pNext = nullptr,
        .flags = VkDeviceCreateFlags(),
        .queueCreateInfoCount = static_cast<std::uint32_t>(queueInfos.size()),
        .pQueueCreateInfos = queueInfos.data(),
        .enabledLayerCount = 0,
        .ppEnabledLayerNames = nullptr,
        .enabledExtensionCount = static_cast<std::uint32_t>(extensions.size()),
        .ppEnabledExtensionNames = extensions.data(),
        .pEnabledFeatures = nullptr
    };

    if (auto res = ::vkCreateDevice(parent().getPhysicalDevice(), &deviceInfo, nullptr, &handle()); res != VK_SUCCESS)
        throw std::runtime_error("LogicalDevice::LogicalDevice: Couldn't create logical device '"_str + ErrorMessage(res) + '\'');
    parent().getQueueHandler().retreiveQueuesHandlers();
#ifndef KUBE_NO_DEBUG
    std::cout << "Logical Extensions:" << std::endl;
    for (auto &extension : extensions)
        std::cout << '\t' << extension << std::endl;
#endif
}

LogicalDevice::Extensions LogicalDevice::getExtensions(void) const
{
    Extensions extensions { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
    std::vector<VkExtensionProperties> properties;

    if (auto res = FillVkContainer(properties, &::vkEnumerateDeviceExtensionProperties, parent().getPhysicalDevice(), nullptr); res != VK_SUCCESS)
        throw std::runtime_error("LogicalDevice::getExtensions: Couldn't enumerate logical device extensions '"_str + ErrorMessage(res) + '\'');
    for (const auto &extension : extensions) {
        auto found = false;
        for (const auto &property : properties) {
            if (found = !std::strcmp(property.extensionName, extension); found)
                break;
        }
        if (!found)
            throw std::runtime_error("Renderer::getLogicalExtensions: Extension '" + std::string(extension) + "' not found");
    }
    return extensions;
}