/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Renderer Helper
 */

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

#include <Kube/Graphics/Renderer.hpp>

auto MakeRenderer(void)
{
    return kF::Graphics::Renderer(
        ::SDL_CreateWindow(
            "KubeBenchmarks",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            800, 600,
            SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE
        )
    );
}