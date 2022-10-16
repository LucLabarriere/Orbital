#pragma once

#include "OrbitalTools/Maths.h"

namespace Orbital
{
    /**
     * @class Inputs
     * @brief A static class that provides functions to query the state of inputs
     */
    class Inputs
    {
    public:
        static Maths::Vec2 getMousePosition();
        static bool isKeyDown(int key);
        static bool isMouseButtonDown(int button);
    };
}
