/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Drawer
 */

#pragma once

#include "Semaphore.hpp"
#include "Fence.hpp"

namespace kF
{
    class Drawer;
    class Renderer;
}

class kF::Drawer final : public RendererObject
{
public:
    Drawer(Renderer &renderer, const std::uint32_t asyncFrameCount = 2);
    Drawer(Drawer &&other) = default;
    ~Drawer(void);

    Drawer &operator=(Drawer &&other) = default;

    void addCommandIndex(const CommandIndex command);
    void removeCommandIndex(const CommandIndex command);
    void clearCommandIndexes(void);

    void draw(void);

    void waitAllDrawCompleted(void);

private:
    std::uint32_t _asyncFrameCount = 0, _currentFrame = 0;
    Semaphores _avaibleSemaphores, _finishedSemaphores;
    Fences _frameFences;
    CommandIndexes _commandIndexes;
    Commands _commands;

    void retreiveFrameCommands(const std::uint32_t imageIndex) noexcept;
    void presentImage(const std::uint32_t imageIndex);
};