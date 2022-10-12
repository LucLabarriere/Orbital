#pragma once

#include "OrbitalRenderer/RenderAPI.h"
#include "OrbitalRenderer/VertexArray.h"
#include "OrbitalRenderer/VertexBuffer.h"
#include "OrbitalRenderer/Shader.h"

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

        float vertices[18] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
             0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
        };

        float vertices2[18] = {
             0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
             0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f
        };

        VertexArray* mVAO;
        VertexArray* mVAO2;
        VertexBuffer* mVBO;
        VertexBuffer* mVBO2;
        Shader* mShader;
    };
}
