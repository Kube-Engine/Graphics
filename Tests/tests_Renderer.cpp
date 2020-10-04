/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Unit tests of renderer
 */

#include <gtest/gtest.h>

#include <Kube/Graphics/Renderer.hpp>

using namespace kF;

TEST(Renderer, InitDestroy)
{
    ASSERT_ANY_THROW(Graphics::Renderer(nullptr));
}

