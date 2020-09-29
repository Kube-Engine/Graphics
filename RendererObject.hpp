/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Interface for child renderer objects
 */

#pragma once

#include <Kube/Core/Core.hpp>

namespace kF
{
    class Renderer;
    class RendererObject;
}

class kF::RendererObject
{
public:
    RendererObject(Renderer &renderer) : _parent(&renderer) {}
    RendererObject(const RendererObject &other) = default;
    RendererObject(RendererObject &&other) = default;

    RendererObject &operator=(const RendererObject &) = default;
    RendererObject &operator=(RendererObject &&) = default;

protected:
    [[nodiscard]] Renderer &parent(void) noexcept { return *_parent; }
    [[nodiscard]] const Renderer &parent(void) const noexcept { return *_parent; }

private:
    Renderer *_parent;
};