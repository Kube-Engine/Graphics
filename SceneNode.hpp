/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Scene Node
 */

#pragma once

#include <atomic>

// #include "CommandModel.hpp"

namespace kF
{
    class SceneNode;
}

class kF::SceneNode
{
public:
    SceneNode(void) = default;
    virtual ~SceneNode(void) = default;

protected:

    void invalidate(void) { _invalidated = true; }

private:
    std::atomic<bool> _busy { false };
    std::atomic<bool> _invalidated { true };
};