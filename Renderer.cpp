/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Renderer sources
 */

#include <stdexcept>

#include <Kube/Core/StringLiteral.hpp>

#include "Renderer.hpp"

using namespace kF;
using namespace kF::Literal;

Graphics::Renderer::GlobalInstance::GlobalInstance(BackendWindow * const window, const Version applicationVersion)
{
    if (_Constructed)
        throw std::logic_error("Graphics::Renderer::GlobalInstance: Renderer already instantiated");
    _Constructed = true;
    _renderer = new (&RendererObject::Parent()) Renderer(window, applicationVersion);
}

Graphics::Renderer::GlobalInstance::~GlobalInstance(void)
{
    _Constructed = false;
    RendererObject::Parent().~Renderer();
}

Graphics::Renderer::Renderer(BackendWindow * const window, const Version applicationVersion) :
    _window(window),
    _instance(applicationVersion)
{
}