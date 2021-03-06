/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Queue Handler
 */

#pragma once

#include <array>

#include <Kube/Core/Vector.hpp>

#include "Vulkan.hpp"
#include "RendererObject.hpp"

namespace kF::Graphics
{
    class QueueManager;

    /** @brief Get a literal of QueueType enumeration */
    [[nodiscard]] constexpr const char *QueueTypeName(const QueueType type) noexcept;
}

/** @brief Handles a list of queues */
class alignas_double_cacheline kF::Graphics::QueueManager final : public CachedRendererObject
{
public:
    /** @brief Describes a queue family and handle */
    struct QueueDescriptor
    {
        std::uint32_t queueFamilyIndex {}; // Index of the queue family
        std::uint32_t queueIndex {}; // Index from specific queue family
        QueueHandle queueHandle {}; // Handle of the queue
    };

    /** @brief The number of different familly queues */
    static constexpr auto QueueCount = static_cast<std::size_t>(QueueType::Count);

    /** @brief An array containing available queue descriptors */
    using QueuesArray = std::array<QueueDescriptor, QueueCount>;

    /** @brief All candidates of a queue family */
    using QueueCandidates = Core::TinyVector<std::pair<std::uint32_t, std::size_t>>;

    /** @brief An array containing all available queue candidates */
    using QueueCandidateMap = std::array<QueueCandidates, QueueCount>;

    /** @brief Describe how to create a queue */
    using QueueCreateInfo = VkDeviceQueueCreateInfo;

    /** @brief Describe how to multiple queues */
    using QueueCreateInfos = Core::TinyVector<QueueCreateInfo>;


    /** @brief Construct queue handler */
    QueueManager(void);

    /** @brief Move constructor */
    QueueManager(QueueManager &&other) noexcept = default;

    /** @brief Destroy queue handler */
    ~QueueManager(void) noexcept = default;

    /** @brief Move assignment */
    QueueManager &operator=(QueueManager &&other) noexcept = default;


    /** @brief Retreive a queue descriptor that match given type and index */
    [[nodiscard]] const QueueDescriptor &queueDescriptor(const QueueType type) const noexcept
        { return _array[static_cast<std::size_t>(type)]; }

    /** @brief Retreive a queue that match given type and index */
    [[nodiscard]] const QueueHandle &queue(const QueueType type) const noexcept
        { return _array[static_cast<std::size_t>(type)].queueHandle; }


    /** @brief Wait until a queue is IDLE */
    void waitQueueIdle(const QueueType queueType) noexcept;


    /**
     * @brief Get a create info list of queues
     *  This function tries to give as much different queues as the hardware can manage
     *  If there isn't enough different queues, it'll use the same queue to assume different queue command types
     */
    [[nodiscard]] QueueCreateInfos registerQueues(void);

    /** @brief Fill internal queues handler using registered queues */
    void retreiveQueuesHandlers(void) noexcept;

private:
    QueuesArray _array;
    QueueCandidateMap _candidates;

    /** @brief Retreive every family queue and indexes that the hardware is capable of */
    void retreiveFamilyQueueIndexes(void);
};

static_assert_alignof_double_cacheline(kF::Graphics::QueueManager);