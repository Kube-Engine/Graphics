/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Drawer
 */

#pragma once

#include "Semaphore.hpp"
#include "Fence.hpp"

namespace kF::Graphics
{
    class Drawer;
    class Renderer;
}

/** @brief Drawer implement the pipeline execution and presentation logic of renderer*/
class kF::Graphics::Drawer final : public RendererObject
{
public:
    /** @brief Construct a drawer with a given number of bufferised frame count */
    Drawer(Renderer &renderer, const std::uint32_t asyncFrameCount = 2);

    /** @brief Move constructor */
    Drawer(Drawer &&other) noexcept = default;

    /** @brief Destruct the drawer */
    ~Drawer(void);

    /** @brief Move assignment */
    Drawer &operator=(Drawer &&other) noexcept = default;

    /** @brief Add a command to be rendered */
    void addCommandIndex(const CommandIndex command);

    /** @brief Remove a command from the renderer list */
    void removeCommandIndex(const CommandIndex command);

    /** @brief Remove all command indexes of the drawer */
    void clearCommandIndexes(void) noexcept;

    /** @brief Draw a frame */
    void draw(void);

    /** @brief Wait until all drawing frame are completed */
    void waitAllDrawCompleted(void);

private:
    std::uint32_t _asyncFrameCount = 0, _currentFrame = 0;
    Semaphores _avaibleSemaphores, _finishedSemaphores;
    Fences _frameFences;
    CommandIndexes _commandIndexes;
    Commands _commands;

    /** @brief Retreive commands of a frame */
    void retreiveFrameCommands(const std::uint32_t imageIndex) noexcept;

    /** @brief Present an image to the screen */
    void presentImage(const std::uint32_t imageIndex);
};