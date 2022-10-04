#pragma once

#include "Context.h"

namespace Orbital
{
    class ORENDERER_API Window
    {
        public:
            Window();

        private:
            GLFWwindow* mGLFWwindow = NULL;
    };
}
