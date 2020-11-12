/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: PhysicalDevice
 */

#pragma once

#include <Kube/Core/Vector.hpp>

#include "VulkanHandle.hpp"

namespace kF::Graphics
{
    class PhysicalDevice;
}

/** @brief A physical device represent a GPU card in the computer */
class kF::Graphics::PhysicalDevice final : public VulkanHandle<PhysicalDeviceHandle>
{
public:
    /** @brief A list of vulkan devices */
    using Devices = Core::TinyVector<PhysicalDeviceHandle>;

    /** @brief Construct a physical device */
    PhysicalDevice(Renderer &renderer);

    /** @brief Move constructor */
    PhysicalDevice(PhysicalDevice &&other) noexcept = default;

    /** @brief Destruct the physical device */
    ~PhysicalDevice(void) noexcept = default;

    /** @brief Move assignment */
    PhysicalDevice &operator=(PhysicalDevice &&other) noexcept = default;

private:
    /** @brief Get the list of physical devices available */
    [[nodiscard]] Devices getDevices(void) const;

    /** @brief Select the best physical device to use */
    void selectDevice(const Devices &devices);
};