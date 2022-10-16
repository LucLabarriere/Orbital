#pragma once

#include "OrbitalTools/Maths.h"

namespace Orbital
{
    struct TransformComponent
    {
        Maths::Vec3 position = { 0.0f, 0.0f, 0.0f };
        Maths::Vec3 rotation = { 0.0f, 0.0f, 0.0f };
        Maths::Vec3 scale = { 1.0f, 1.0f, 1.0f };
    };
}
