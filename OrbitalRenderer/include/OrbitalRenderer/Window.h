#pragma once
#include "Context.h"

namespace Orbital
{
    class ORENDERER_API Window
    {
    public: 
        virtual ~Window() {  }
        static Window* Create();

        virtual void swapBuffers() const = 0;
        virtual bool initialize() = 0;
        virtual void* getNativeWindow() = 0;
        virtual bool shouldClose() const = 0;
    };
}
