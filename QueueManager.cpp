/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Queue Handler
 */

#include <iostream>

#include <Kube/Core/StringLiteral.hpp>

#include "Renderer.hpp"
#include "QueueManager.hpp"

using namespace kF;
using namespace kF::Literal;

Graphics::QueueManager::QueueManager(Renderer &renderer)
    : RendererObject(renderer)
{
    retreiveFamilyQueueIndexes();
#if KUBE_DEBUG_BUILD
    std::cout << "Queues:" << std::endl;
    for (auto type = 0u; type < QueueType::Count; ++type) {
        std::cout << '\t' << QueueTypeName(static_cast<QueueType>(type)) << ": ";
        if (!_candidates[type].empty()) {
            std::cout << _candidates[type].size() << " queues available: " << std::endl;
            for (auto index : _candidates[type]) {
                std::cout << "\t\t-> ";
                if (index.first == queueDescriptor(static_cast<QueueType>(type)).queueFamilyIndex)
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

void Graphics::QueueManager::retreiveQueuesHandlers(void) noexcept
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
        ::vkGetDeviceQueue(parent().logicalDevice(), desc.queueFamilyIndex, desc.queueIndex, &desc.queueHandle);
        past.emplace_back(&desc);
    }
}

Graphics::QueueManager::QueueCreateInfos Graphics::QueueManager::registerQueues(void)
{
    static const float priority = 1.0f;

    Core::TinyVector<std::uint32_t> usedIndexes;
    QueueCreateInfos queues;

    for (std::size_t type = 0u; type < static_cast<std::size_t>(QueueType::Count); ++type) {
        if (_candidates[type].empty()) {
            if (static_cast<QueueType>(type) == QueueType::FastTransfer)
                continue;
            throw std::runtime_error("Graphics::QueueManager::registerQueues: Couldn't register unsupported queue type '"s + QueueTypeName(static_cast<QueueType>(type)));
        }
        bool found = false;
        std::pair<std::uint32_t, std::size_t> best(0, usedIndexes.size() + 1);
        for (const auto [queueFamilyIndex, queueCount] : _candidates[type]) {
            const std::size_t score = std::count(usedIndexes.begin(), usedIndexes.end(), queueFamilyIndex);
            if (score < queueCount) {
                if (!score)
                    queues.push(QueueCreateInfo {
                        sType: VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
                        pNext: nullptr,
                        flags: VkDeviceQueueCreateFlags(),
                        queueFamilyIndex: queueFamilyIndex,
                        queueCount: 1,
                        pQueuePriorities: &priority
                    });
                else
                    for (auto &queue : queues) {
                        if (queue.queueFamilyIndex == queueFamilyIndex) {
                            ++queue.queueCount;
                            break;
                        }
                    }
                usedIndexes.push(queueFamilyIndex);
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
            usedIndexes.push(best.first);
            _array[type].queueFamilyIndex = best.first;
            _array[type].queueIndex = 0;
        }
    }
    return queues;
}

void Graphics::QueueManager::retreiveFamilyQueueIndexes(void)
{
    constexpr auto TypeToFlags = [](const QueueType type) -> VkQueueFlags {
        switch (type) {
        case QueueType::Graphics:
            return VK_QUEUE_GRAPHICS_BIT;
        case QueueType::Compute:
            return VK_QUEUE_COMPUTE_BIT;
        case QueueType::Transfer:
        case QueueType::FastTransfer:
            return VK_QUEUE_TRANSFER_BIT;
        default:
            return VK_QUEUE_FAMILY_IGNORED;
        }
    };

    Core::Vector<VkQueueFamilyProperties> properties;
    std::uint32_t queueFamilyIndex = 0;
    VkBool32 isPresent = false;

    FillVkContainer(properties, &::vkGetPhysicalDeviceQueueFamilyProperties, parent().physicalDevice());
    for (auto &property : properties) {
        if (auto res = ::vkGetPhysicalDeviceSurfaceSupportKHR(parent().physicalDevice(), queueFamilyIndex, parent().surface(), &isPresent); res != VK_SUCCESS)
            throw std::runtime_error("Graphics::QueueManager::registerQueues: Couldn't get physical device surface support '"s + ErrorMessage(res) + '\'');
        if (isPresent)
            _candidates[static_cast<std::size_t>(QueueType::Present)].push(queueFamilyIndex, property.queueCount);
        if (property.queueFlags & TypeToFlags(QueueType::Graphics))
            _candidates[static_cast<std::size_t>(QueueType::Graphics)].push(queueFamilyIndex, property.queueCount);
        if (property.queueFlags & TypeToFlags(QueueType::Compute))
            _candidates[static_cast<std::size_t>(QueueType::Compute)].push(queueFamilyIndex, property.queueCount);
        if (property.queueFlags & TypeToFlags(QueueType::SparseBinding))
            _candidates[static_cast<std::size_t>(QueueType::Compute)].push(queueFamilyIndex, property.queueCount);
        if (property.queueFlags & TypeToFlags(QueueType::Transfer)) {
            _candidates[static_cast<std::size_t>(QueueType::Transfer)].push(queueFamilyIndex, property.queueCount);
            if (!(property.queueFlags & TypeToFlags(QueueType::Graphics)) && !(property.queueFlags & TypeToFlags(QueueType::Compute)) )
                _candidates[static_cast<std::size_t>(QueueType::FastTransfer)].push(queueFamilyIndex, property.queueCount);
        }
        ++queueFamilyIndex;
    }
}

constexpr const char *kF::Graphics::QueueTypeName(const QueueType type) noexcept
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