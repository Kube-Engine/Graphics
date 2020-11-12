/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: BufferModel
 */

inline kF::Graphics::BufferModel kF::Graphics::BufferModel::MakeStaging(const BufferSize size) noexcept
{
    return BufferModel(
        BufferCreateFlags::None, size,
        BufferUsageFlags::TransferSrc, SharingMode::Exclusive,
        nullptr, nullptr
    );
}

inline kF::Graphics::BufferModel kF::Graphics::BufferModel::MakeVertexLocal(const BufferSize size) noexcept
{
    return BufferModel(
        BufferCreateFlags::None, size,
        MakeFlags(BufferUsageFlags::TransferDst, BufferUsageFlags::VertexBuffer), SharingMode::Exclusive,
        nullptr, nullptr
    );
}

inline kF::Graphics::BufferModel kF::Graphics::BufferModel::MakeVertexShared(const BufferSize size) noexcept
{
    return BufferModel(
        BufferCreateFlags::None, size,
        BufferUsageFlags::VertexBuffer, SharingMode::Exclusive,
        nullptr, nullptr
    );
}

inline kF::Graphics::BufferModel kF::Graphics::BufferModel::MakeIndexLocal(const BufferSize size) noexcept
{
    return BufferModel(
        BufferCreateFlags::None, size,
        MakeFlags(BufferUsageFlags::TransferDst, BufferUsageFlags::IndexBuffer), SharingMode::Exclusive,
        nullptr, nullptr
    );
}

inline kF::Graphics::BufferModel kF::Graphics::BufferModel::MakeIndexShared(const BufferSize size) noexcept
{
    return BufferModel(
        BufferCreateFlags::None, size,
        BufferUsageFlags::IndexBuffer, SharingMode::Exclusive,
        nullptr, nullptr
    );
}
