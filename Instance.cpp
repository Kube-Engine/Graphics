/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Instance
 */

#include <cstring>
#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

#include <Kube/Core/StringLiteral.hpp>

#include "Renderer.hpp"
#include "Instance.hpp"

using namespace kF;
using namespace kF::Literal;


Graphics::Instance::~Instance(void) noexcept
{
    ::vkDestroyInstance(handle(), nullptr);
}

void Graphics::Instance::createInstance(const Version applicationVersion)
{
    auto layers = getLayers();
    auto extensions = getExtensions(parent().backendWindow());
    VkApplicationInfo appInfo {
        sType: VK_STRUCTURE_TYPE_APPLICATION_INFO,
        pNext: nullptr,
        pApplicationName: ::SDL_GetWindowTitle(parent().backendWindow()),
        applicationVersion: static_cast<std::uint32_t>(VK_MAKE_VERSION(applicationVersion.major, applicationVersion.minor, applicationVersion.patch)),
        pEngineName: "Kube",
        engineVersion: static_cast<std::uint32_t>(VK_MAKE_VERSION(KubeVersion.major, KubeVersion.minor, KubeVersion.patch)),
        apiVersion: VK_API_VERSION_1_1
    };
    VkInstanceCreateInfo instanceInfo {
        sType: VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        pNext: nullptr,
        flags: VkInstanceCreateFlags(),
        pApplicationInfo: &appInfo,
        enabledLayerCount: static_cast<std::uint32_t>(layers.size()),
        ppEnabledLayerNames: layers.data(),
        enabledExtensionCount: static_cast<std::uint32_t>(extensions.size()),
        ppEnabledExtensionNames: extensions.data()
    };

    if (const auto res = ::vkCreateInstance(&instanceInfo, nullptr, &handle()); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::Instance::Instance: Couldn't create instance '"s + ErrorMessage(res) + '\'');
#if KUBE_DEBUG_BUILD
    std::cout << "Extensions:" << std::endl;
    for (auto &extension : extensions)
        std::cout << '\t' << extension << std::endl;
    std::cout << "Layers:" << std::endl;
    for (auto &layer : layers)
        std::cout << '\t' << layer << std::endl;
#endif
}

Graphics::Instance::Layers Graphics::Instance::getLayers(void) const
{
#if KUBE_DEBUG_BUILD
    Layers layers { "VK_LAYER_KHRONOS_validation" };
    std::uint32_t count = 0;
    std::vector<VkLayerProperties> avaible;

    if (const auto res = ::vkEnumerateInstanceLayerProperties(&count, nullptr); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::Instance::getLayers: Couldn't enumerate instances layers properties"s + ErrorMessage(res) + '\'');
    if (!count)
        return layers;
    avaible.resize(count + layers.size());
    if (const auto res = ::vkEnumerateInstanceLayerProperties(&count, avaible.data()); res != VK_SUCCESS)
        throw std::runtime_error("Graphics::Instance::getLayers: Couldn't enumerate instances layers properties"s + ErrorMessage(res) + '\'');
    for (auto it = layers.begin(); it != layers.end();) {
        bool found = false;
        for (const auto &layerProperties : avaible) {
            if (found = !std::strcmp(*it, layerProperties.layerName); found)
                break;
        }
        if (found)
            ++it;
        else {
            std::cerr << "Graphics::Instance::getLayers: Couldn't use debug layer '" << *it << '\'' << std::endl;
            it = layers.erase(it);
        }
    }
    return layers;
#else
    return Layers();
#endif
}

Graphics::Instance::Extensions Graphics::Instance::getExtensions(BackendWindow *window) const
{
    Extensions extensions;
    std::uint32_t count = 0;

    if (!::SDL_Vulkan_GetInstanceExtensions(window, &count, nullptr))
        throw std::runtime_error("Graphics::Instance::getExtensions: Couldn't retreive instance extensions '"s + ::SDL_GetError() + '\'');
    if (!count)
        return extensions;
    extensions.resize(count);
    if (!::SDL_Vulkan_GetInstanceExtensions(window, &count, extensions.data()))
        throw std::runtime_error("Graphics::Instance::getExtensions: Couldn't retreive instance extensions '"s + ::SDL_GetError() + '\'');
    return extensions;
}