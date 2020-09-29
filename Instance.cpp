/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Instance
 */

#include <cstring>
#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

#include <Kube/Core/Core.hpp>

#include "Renderer.hpp"

using namespace kF;
using namespace kF::Literal;

Instance::Instance(Renderer &renderer, const Version applicationVersion)
    : VulkanHandler<VkInstance>(renderer)
{
    createInstance(applicationVersion);
}

Instance::~Instance(void)
{
    ::vkDestroyInstance(handle(), nullptr);
}

void Instance::createInstance(const Version applicationVersion)
{
    auto layers = getLayers();
    auto extensions = getExtensions(parent().getBackendWindow());
    VkApplicationInfo appInfo {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pNext = nullptr,

        .pApplicationName = ::SDL_GetWindowTitle(parent().getBackendWindow()),
        .applicationVersion = static_cast<std::uint32_t>(VK_MAKE_VERSION(applicationVersion.major, applicationVersion.minor, applicationVersion.patch)),
        .pEngineName = "Kube",
        .engineVersion = static_cast<std::uint32_t>(VK_MAKE_VERSION(KubeVersion.major, KubeVersion.minor, KubeVersion.patch)),
        .apiVersion = VK_API_VERSION_1_1
    };
    VkInstanceCreateInfo instanceInfo {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pNext = nullptr,
        .flags = VkInstanceCreateFlags(),
        .pApplicationInfo = &appInfo,
        .enabledLayerCount = static_cast<std::uint32_t>(layers.size()),
        .ppEnabledLayerNames = layers.data(),
        .enabledExtensionCount = static_cast<std::uint32_t>(extensions.size()),
        .ppEnabledExtensionNames = extensions.data()
    };

    if (auto res = ::vkCreateInstance(&instanceInfo, nullptr, &handle()); res != VK_SUCCESS)
        throw std::runtime_error("Instance::Instance: Couldn't create instance '"_str + ErrorMessage(res) + '\'');
#ifndef KUBE_NO_DEBUG
    std::cout << "Extensions:" << std::endl;
    for (auto &extension : extensions)
        std::cout << '\t' << extension << std::endl;
    std::cout << "Layers:" << std::endl;
    for (auto &layer : layers)
        std::cout << '\t' << layer << std::endl;
#endif
}

Instance::Layers Instance::getLayers(void) const
{
#ifndef KUBE_NO_DEBUG
    Layers layers { "VK_LAYER_KHRONOS_validation" };
    std::uint32_t count = 0;
    std::vector<VkLayerProperties> avaible;

    if (auto res = ::vkEnumerateInstanceLayerProperties(&count, nullptr); res != VK_SUCCESS)
        throw std::runtime_error("Instance::getLayers: Couldn't enumerate instances layers properties"_str + ErrorMessage(res) + '\'');
    if (!count)
        return layers;
    avaible.resize(count + layers.size());
    if (auto res = ::vkEnumerateInstanceLayerProperties(&count, avaible.data()); res != VK_SUCCESS)
        throw std::runtime_error("Instance::getLayers: Couldn't enumerate instances layers properties"_str + ErrorMessage(res) + '\'');
    for (auto it = layers.begin(); it != layers.end();) {
        bool found = false;
        for (const auto &layerProperties : avaible) {
            if (found = !std::strcmp(*it, layerProperties.layerName); found)
                break;
        }
        if (found)
            ++it;
        else {
            std::cerr << "Instance::getLayers: Couldn't use debug layer '" << *it << '\'' << std::endl;
            it = layers.erase(it);
        }
    }
    return layers;
#else
    return Layers();
#endif
}

Instance::Extensions Instance::getExtensions(BackendWindow *window) const
{
    Extensions extensions;
    std::uint32_t count = 0;

    if (!::SDL_Vulkan_GetInstanceExtensions(window, &count, nullptr))
        throw std::runtime_error("Instance::getExtensions: Couldn't retreive instance extensions '"_str + ::SDL_GetError() + '\'');
    if (!count)
        return extensions;
    extensions.resize(count);
    if (!::SDL_Vulkan_GetInstanceExtensions(window, &count, extensions.data()))
        throw std::runtime_error("Instance::getExtensions: Couldn't retreive instance extensions '"_str + ::SDL_GetError() + '\'');
    return extensions;
}