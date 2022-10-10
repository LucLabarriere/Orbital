#pragma once

#include "OrbitalRenderer/RenderAPI.h"

namespace Orbital
{
    class Window;

    class LowRenderer
    {
    public:
        LowRenderer();
        LowRenderer(LowRenderer &&) = delete;
        LowRenderer(const LowRenderer &) = delete;
        LowRenderer &operator=(LowRenderer &&) = delete;
        LowRenderer &operator=(const LowRenderer &) = delete;
        virtual ~LowRenderer();
  
        void initialize();
        void terminate();
        
    private:
        Window* mWindow;
    };
}
