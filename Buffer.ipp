/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Buffer
 */

inline kF::Graphics::Buffer::Buffer(Renderer &renderer, const BufferModel &model) : VulkanHandler<BufferHandle>(renderer)
{
    createBufferHandle(model);
    createDeviceMemory(model);
    fillMemory(model);
}

inline void kF::Graphics::Buffer::swap(Buffer &other) noexcept
{
    VulkanHandler<BufferHandle>::swap(other);
    std::swap(_memory, other._memory);
}


