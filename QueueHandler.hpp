/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Queue Handler
 */

#pragma once

#include <array>
#include <memory>

#include "RendererObject.hpp"

namespace kF::Graphics
{
    class QueueHandler;

    /** @brief A vulkan queue */
    using Queue = VkQueue;

    /** @brief Describes all types of queues */
    enum class QueueType {
        Graphics = 0,
        Compute,
        Transfer,
        FastTransfer,
        Present,
        Count
    };

    /** @brief Get a literal of QueueType enumeration */
    [[nodiscard]] constexpr const char *QueueTypeName(const QueueType type) noexcept;
}

/** @brief Handles a list of queues */
class kF::Graphics::QueueHandler final : public RendererObject
{
public:
    /** @brief a Queue instance has a reference count */
    using QueueInstance = std::shared_ptr<Queue>;

    /** @brief Describes a queue */
    struct QueueDescriptor
    {
        std::uint32_t queueFamilyIndex {}; // Index of the queue family
        std::uint32_t queueIndex {}; // Index from specific queue family
        Queue queueHandle {};
    };

    /** @brief The number of different familly queues */
    static constexpr auto QueueCount = static_cast<std::size_t>(QueueType::Count);

    /** @brief An array containing available queue descriptors */
    using QueuesArray = std::array<QueueDescriptor, QueueCount>;

    /** @brief All candidates of a queue family */
    using QueueCandidates = std::vector<std::pair<std::uint32_t, std::size_t>>;

    /** @brief An array containing all available queue candidates */
    using QueueCandidateMap = std::array<QueueCandidates, QueueCount>;

    /** @brief Describe how to create a queue */
    using QueueCreateInfo = VkDeviceQueueCreateInfo;

    /** @brief Describe how to multiple queues */
    using QueueCreateInfos = std::vector<QueueCreateInfo>;

    /** @brief Construct queue handler */
    QueueHandler(Renderer &renderer);

    /** @brief Move constructor */
    QueueHandler(QueueHandler &&other) noexcept = default;

    /** @brief Destroy queue handler */
    ~QueueHandler(void) noexcept = default;

    /** @brief Move assignment */
    QueueHandler &operator=(QueueHandler &&other) noexcept = default;

    /** @brief Retreive a queue descriptor that match given type and index */
    [[nodiscard]] const QueueDescriptor &queueDescriptor(const QueueType type) const noexcept
        { return _array[static_cast<std::size_t>(type)]; }

    /** @brief Retreive a queue that match given type and index */
    [[nodiscard]] const Queue &getQueue(const QueueType type) const noexcept
        { return _array[static_cast<std::size_t>(type)].queueHandle; }

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

    /** @brief Converts a queue type into its string name */
    [[nodiscard]] static constexpr std::uint32_t TypeToFlag(const QueueType type) noexcept;
};
