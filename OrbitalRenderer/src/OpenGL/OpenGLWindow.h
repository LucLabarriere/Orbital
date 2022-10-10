#pragma once
#include "OrbitalRenderer/Window.h"

namespace Orbital
{
    class OpenGLWindow : public Window
    {
    public:
        OpenGLWindow();
        virtual ~OpenGLWindow() override {  };
        
        virtual void swapBuffers() override;
        virtual bool initialize() override;
        virtual bool shouldClose() const override;

    private:
        GLFWwindow* mGLFWwindow = nullptr;
    };
}
