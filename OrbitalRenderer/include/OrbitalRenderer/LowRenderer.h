#pragma once

#include "OrbitalRenderer/VertexArray.h"

namespace Orbital
{
    class Window;

    class ORENDERER_API LowRenderer
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
        void render(const VertexArray& vao, size_t vertexCount);
        
    private:
        Window* mWindow;
    };
}
