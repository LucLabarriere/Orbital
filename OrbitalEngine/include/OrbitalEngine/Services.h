#pragma once

namespace Orbital
{
    class Window;
    class HighRenderer;
    
    struct Services
    {
        Window* window = nullptr;
        HighRenderer* renderer = nullptr;
    };
}
