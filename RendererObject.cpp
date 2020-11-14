/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: RendererObject
 */

#include "Renderer.hpp"

using namespace kF;

alignas(alignof(Graphics::Renderer)) static std::byte ParentRendererBytes[sizeof(Graphics::Renderer)];

Graphics::Renderer &Graphics::RendererObject::Parent(void) noexcept
{
    return reinterpret_cast<Renderer &>(ParentRendererBytes);
}