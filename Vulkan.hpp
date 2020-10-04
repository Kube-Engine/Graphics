/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Vulkan utils
 */

#pragma once

#include <utility>
#include <cinttypes>
#include <vulkan/vulkan.h>

namespace kF::Graphics
{
    /** @brief Get an error message from a vulkan result */
    [[nodiscard]] const char *ErrorMessage(VkResult res);

    /** @brief Fill a container using a vulkan style getter with VkResult as return type */
    template<typename Container, typename ...FunctionArgs, typename ...Args>
    [[nodiscard]] VkResult FillVkContainer(Container &container, VkResult(*function)(FunctionArgs...), Args &&...args)
    {
        std::uint32_t count = 0;
        VkResult res = (*function)(std::forward<Args>(args)..., &count, nullptr);
        if (res != VK_SUCCESS || !count)
            return res;
        container.resize(count);
        return (*function)(std::forward<Args>(args)..., &count, container.data());
    }

    /** @brief Fill a container using a vulkan style getter with void as return type */
    template<typename Container, typename ...FunctionArgs, typename ...Args>
    void FillVkContainer(Container &container, void(*function)(FunctionArgs...), Args &&...args)
    {
        std::uint32_t count = 0;
        (*function)(std::forward<Args>(args)..., &count, nullptr);
        if (!count)
            return;
        container.resize(count);
        (*function)(std::forward<Args>(args)..., &count, container.data());
    }

}