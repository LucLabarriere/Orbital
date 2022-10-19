#pragma once
#include "OrbitalRenderer/Window.h"
#include "OrbitalRenderer/RendererContext.h"

namespace Orbital
{
    class ORENDERER_API OpenGLWindow : public Window
    {
    public:
        OpenGLWindow();
        virtual ~OpenGLWindow() override {  };
        
        virtual void swapBuffers() const override;
        virtual bool initialize() override;
        virtual void* getNativeWindow() override;
        virtual bool shouldClose() const override;

    private:
        GLFWwindow* mGLFWwindow = nullptr;
    };
}
