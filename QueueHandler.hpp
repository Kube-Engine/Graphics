/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Queue Handler
 */

#pragma once

#include <array>
#include <memory>

#include "RendererObject.hpp"

namespace kF
{
    class QueueHandler;

    enum QueueType {
        Graphics = 0,
        Compute,
        Transfer,
        FastTransfer,
        Present,
        QueueTypeCount
    };

    using Queue = VkQueue;

    [[nodiscard]] constexpr const char *QueueTypeName(const QueueType type) noexcept;
}

class kF::QueueHandler final : public RendererObject
{
public:
    using QueueInstance = std::shared_ptr<Queue>;

    struct QueueDescriptor
    {
        std::uint32_t queueFamilyIndex {};
        std::uint32_t queueIndex {}; // Index from specific queue family
        Queue queueHandle {};
    };

    using QueuesArray = std::array<QueueDescriptor, QueueType::QueueTypeCount>;
    using QueueCandidateMap = std::array<std::vector<std::pair<std::uint32_t, std::size_t>>, QueueType::QueueTypeCount>;
    using QueueCreateInfo = VkDeviceQueueCreateInfo;
    using QueueCreateInfos = std::vector<QueueCreateInfo>;

    /** @brief Construct a new Queue Handler object */
    QueueHandler(Renderer &renderer);

    /** @brief Construct a new Queue Handler object by move */
    QueueHandler(QueueHandler &&other) = default;

    /** @brief Destroy the Queue Handler object */
    ~QueueHandler(void) = default;

    /** @brief Move assign a Queue Handler object */
    QueueHandler &operator=(QueueHandler &&other) = default;

    /** @brief Retreive a queue descriptor that match given type and index */
    [[nodiscard]] const QueueDescriptor &getQueueDescriptor(const QueueType type) const noexcept { return _array[type]; }

    /** @brief Retreive a queue that match given type and index */
    [[nodiscard]] const Queue &getQueue(const QueueType type) const noexcept { return _array[type].queueHandle; }

    /**
     * @brief Get a create info list of queues
     *  This function tries to give as much different queues as the hardware can manage
     *  If there isn't enough different queues, it'll use the same queue to assume different queue command types
     */
    [[nodiscard]] QueueCreateInfos registerQueues(void);

    /** @brief Fill internal queues handler using registered queues */
    void retreiveQueuesHandlers(void);

private:
    QueuesArray _array;
    QueueCandidateMap _candidates;

    /** @brief Retreive every family queue and indexes that the hardware is capable of */
    void retreiveFamilyQueueIndexes(void);

    /** @brief Converts a queue type into its string name */
    [[nodiscard]] static constexpr std::uint32_t TypeToFlag(const QueueType type) noexcept;
};
