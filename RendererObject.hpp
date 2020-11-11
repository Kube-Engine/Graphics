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
}

/** @brief This is the base class of all renderer sub objects
 * This class is not virtual because it is trivially destructible
*/
class alignas_eighth_cacheline kF::Graphics::RendererObject
{
public:
    /** @brief Construct a new object */
    RendererObject(Renderer &renderer) noexcept : _parent(&renderer) {}

    /** @brief Copy constructor */
    RendererObject(const RendererObject &other) noexcept = default;

    /** @brief Move constructor */
    RendererObject(RendererObject &&other) noexcept = default;

    /** @brief Default non virtual constructor */
    ~RendererObject(void) noexcept = default;

    /** @brief Copy assignment */
    RendererObject &operator=(const RendererObject &other) noexcept = default;

    /** @brief Move assignment */
    RendererObject &operator=(RendererObject &&other) noexcept = default;

    /** @brief Swap two instances */
    void swap(RendererObject &other) noexcept { std::swap(_parent, other._parent); }

protected:
    /** @brief Get parent renderer */
    [[nodiscard]] Renderer &parent(void) const noexcept { return *_parent; }

private:
    Renderer *_parent;
};