#include "OrbitalInputs/Context.h"
#include "OrbitalInputs/Inputs.h"

namespace Orbital
{

    Maths::Vec2 Inputs::getMousePosition()
    {
        double xPos, yPos;
        glfwGetCursorPos(glfwGetCurrentContext(), &xPos, &yPos);
        return Maths::Vec2((float)xPos, (float)yPos);
    }

    bool Inputs::isKeyDown(int key)
    {
        return glfwGetKey(glfwGetCurrentContext(), key) == GLFW_PRESS ? true : false;
    }

    bool Inputs::isMouseButtonDown(int button)
    {
        return glfwGetMouseButton(glfwGetCurrentContext(), button) == GLFW_PRESS ? true : false;
    }
}
