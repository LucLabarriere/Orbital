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

        Window& getWindow() { return *mWindow; }
  
        void initialize();
        void terminate();
        void render(unsigned int vao, unsigned int vbo);
        
    private:
        Window* mWindow;

        float vertices[9] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };
        unsigned int vao = 0;
        unsigned int vbo = 0;
    };
}
