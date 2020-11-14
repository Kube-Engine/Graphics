/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: RendererObject
 */

#include "Renderer.hpp"

using namespace kF;

struct alignas(alignof(Graphics::Renderer)) RendererCache
{
    std::byte bytes[sizeof(Graphics::Renderer)];
};

static RendererCache ParentRendererBytes {};

Graphics::Renderer &Graphics::RendererObject::Parent(void) noexcept
{
    return reinterpret_cast<Renderer &>(ParentRendererBytes);
}