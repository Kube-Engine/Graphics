/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Interface for child renderer objects
 */

#pragma once

#include <Kube/Core/Utils.hpp>

namespace kF::Graphics
{
    class Renderer;
    class RendererObject;
    class CachedRendererObject;
}

/** @brief This is the base class of all renderer sub objects
 * This class is not virtual because it is trivially destructible */
class kF::Graphics::RendererObject
{
public:
    /** @brief Get global parent renderer */
    [[nodiscard]] Renderer &parent(void) const noexcept { return Parent(); }

    /** @brief Get global parent renderer */
    [[nodiscard]] static Renderer &Parent(void) noexcept;
};

/** @brief This class specializes the RendererObject to hold its parent renderer in its member cache
 * This class is not virtual because it is trivially destructible */
class alignas_eighth_cacheline kF::Graphics::CachedRendererObject : public RendererObject
{
public:
    /** @brief Default constructor */
    CachedRendererObject(void) noexcept : _parent(&Parent()) {}

    /** @brief Copy constructor */
    CachedRendererObject(const CachedRendererObject &other) noexcept = default;

    /** @brief Move constructor */
    CachedRendererObject(CachedRendererObject &&other) noexcept = default;

    /** @brief Copy assignment */
    CachedRendererObject &operator=(const CachedRendererObject &other) noexcept = default;

    /** @brief Move assignment */
    CachedRendererObject &operator=(CachedRendererObject &&other) noexcept = default;

    /** @brief Swap two instances */
    void swap(CachedRendererObject &other) noexcept { std::swap(_parent, other._parent); }


    /** @brief Get cached parent renderer */
    [[nodiscard]] Renderer &parent(void) const noexcept { return *_parent; }


private:
    Renderer *_parent { nullptr };

    using RendererObject::parent;
};