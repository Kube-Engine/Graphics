/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Queue Handler
 */

#include <iostream>

#include <Kube/Core/Core.hpp>

#include "Renderer.hpp"

using namespace kF;
using namespace kF::Literal;

QueueHandler::QueueHandler(Renderer &renderer)
    : RendererObject(renderer)
{
    retreiveFamilyQueueIndexes();
#ifndef KUBE_NO_DEBUG
    std::cout << "Queues:" << std::endl;
    for (auto type = 0u; type < QueueType::QueueTypeCount; ++type) {
        std::cout << '\t' << QueueTypeName(static_cast<QueueType>(type)) << ": ";
        if (!_candidates[type].empty()) {
            std::cout << _candidates[type].size() << " queues available: " << std::endl;
            for (auto index : _candidates[type]) {
                std::cout << "\t\t-> ";
                if (index.first == getQueueDescriptor(static_cast<QueueType>(type)).queueFamilyIndex)
                    std::cout << '\'' << index.first << '\'';
                else
                    std::cout << index.first;
                std::cout << " (x " << index.second << ')' << std::endl;
            }
        } else
            std::cout << "Unsupported" << std::endl;
    }
#endif
}

void QueueHandler::retreiveQueuesHandlers(void)
{
    std::vector<QueueDescriptor *> past;

    for (auto &desc : _array) {
        auto it = std::find_if(past.begin(), past.end(), [&desc](const auto *p) {
            return desc.queueFamilyIndex == p->queueFamilyIndex && desc.queueIndex == p->queueIndex;
        });
        if (it != past.end()) {
            desc.queueHandle = (*it)->queueHandle;
            continue;
        }
        ::vkGetDeviceQueue(parent().getLogicalDevice(), desc.queueFamilyIndex, desc.queueIndex, &desc.queueHandle);
        past.emplace_back(&desc);
    }
}

QueueHandler::QueueCreateInfos QueueHandler::registerQueues(void)
{
    static const float priority = 1.0f;

    std::vector<std::uint32_t> usedIndexes;
    QueueHandler::QueueCreateInfos queues;

    for (std::size_t type = 0; type < QueueType::QueueTypeCount; ++type) {
        if (_candidates[type].empty()) {
            if (type == QueueType::FastTransfer)
                continue;
            throw std::runtime_error("QueueHandler::registerQueues: Couldn't register unsupported queue type '"_str + QueueTypeName(static_cast<QueueType>(type)));
        }
        bool found = false;
        std::pair<std::uint32_t, std::size_t> best(0, usedIndexes.size() + 1);
        for (const auto [queueFamilyIndex, queueCount] : _candidates[type]) {
            auto score = std::count(usedIndexes.begin(), usedIndexes.end(), queueFamilyIndex);
            if (score < queueCount) {
                if (!score)
                    queues.emplace_back(QueueCreateInfo {
                        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
                        .pNext = nullptr,
                        .flags = VkDeviceQueueCreateFlags(),
                        .queueFamilyIndex = queueFamilyIndex,
                        .queueCount = 1,
                        .pQueuePriorities = &priority
                    });
                else
                    for (auto &queue : queues) {
                        if (queue.queueFamilyIndex == queueFamilyIndex) {
                            ++queue.queueCount;
                            break;
                        }
                    }
                usedIndexes.emplace_back(queueFamilyIndex);
                _array[type].queueFamilyIndex = queueFamilyIndex;
                _array[type].queueIndex = score;
                found = true;
                break;
            } else if (score < best.second) {
                best.first = queueFamilyIndex;
                best.second = best.second;
            }
        }
        if (!found) {
            usedIndexes.emplace_back(best.first);
            _array[type].queueFamilyIndex = best.first;
            _array[type].queueIndex = 0;
        }
    }
    return queues;
}

void QueueHandler::retreiveFamilyQueueIndexes(void)
{
    std::vector<VkQueueFamilyProperties> properties;
    std::uint32_t queueFamilyIndex = 0;
    VkBool32 isPresent = false;

    FillVkContainer(properties, &::vkGetPhysicalDeviceQueueFamilyProperties, parent().getPhysicalDevice());
    for (auto &property : properties) {
        if (auto res = ::vkGetPhysicalDeviceSurfaceSupportKHR(parent().getPhysicalDevice(), queueFamilyIndex, parent().getSurface(), &isPresent); res != VK_SUCCESS)
            throw std::runtime_error("QueueHandler::registerQueues: Couldn't get physical device surface support '"_str + ErrorMessage(res) + '\'');
        if (isPresent)
            _candidates[QueueType::Present].emplace_back(queueFamilyIndex, property.queueCount);
        if (property.queueFlags & TypeToFlag(QueueType::Graphics))
            _candidates[QueueType::Graphics].emplace_back(queueFamilyIndex, property.queueCount);
        if (property.queueFlags & TypeToFlag(QueueType::Compute))
            _candidates[QueueType::Compute].emplace_back(queueFamilyIndex, property.queueCount);
        if (property.queueFlags & TypeToFlag(QueueType::Transfer))
            _candidates[QueueType::Transfer].emplace_back(queueFamilyIndex, property.queueCount);
        if (property.queueFlags & TypeToFlag(QueueType::Transfer) && !(property.queueFlags & TypeToFlag(QueueType::Graphics)) && !(property.queueFlags & TypeToFlag(QueueType::Compute)) )
            _candidates[QueueType::FastTransfer].emplace_back(queueFamilyIndex, property.queueCount);
        ++queueFamilyIndex;
    }
}

constexpr std::uint32_t QueueHandler::TypeToFlag(const QueueType type) noexcept
{
    switch (type) {
    case QueueType::Graphics:
        return VK_QUEUE_GRAPHICS_BIT;
    case QueueType::Compute:
        return VK_QUEUE_COMPUTE_BIT;
    case QueueType::Transfer:
        return VK_QUEUE_TRANSFER_BIT;
    default:
        return VK_QUEUE_FAMILY_IGNORED;
    }
}

constexpr const char *kF::QueueTypeName(const QueueType type) noexcept
{
    switch (type) {
    case (QueueType::Graphics):
        return "Graphics";
    case (QueueType::Compute):
        return "Compute";
    case (QueueType::Transfer):
        return "Transfer";
    case (QueueType::FastTransfer):
        return "FastTransfer";
    case (QueueType::Present):
        return "Present";
    default:
        return "InvalidQueueIndex";
    }
}