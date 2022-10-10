#pragma once

#include "Context.h"

namespace Orbital
{
    class Window
    {
    public: 
        virtual ~Window() {  }
        static Window* Create();

        virtual void swapBuffers() = 0;
        virtual bool initialize() = 0;
        virtual bool shouldClose() const = 0;
    };
}
