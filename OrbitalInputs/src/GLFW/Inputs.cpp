#include "OrbitalInputs/Context.h"
#include "OrbitalInputs/Inputs.h"

namespace Orbital
{
    Maths::Vec2 Inputs::GetMousePosition()
    {
        double xPos, yPos;
        glfwGetCursorPos(static_cast<GLFWwindow*>(mContext), &xPos, &yPos);
        return Maths::Vec2((float)xPos, (float)yPos);
    }

    bool Inputs::IsKeyDown(int key)
    {
        return glfwGetKey(static_cast<GLFWwindow*>(mContext), key) == GLFW_PRESS ? true : false;
    }

    bool Inputs::IsMouseButtonDown(int button)
    {
        return glfwGetMouseButton(static_cast<GLFWwindow*>(mContext), button) == GLFW_PRESS ? true : false;
    }

    void Inputs::SetContext(void* context)
    {
        mContext = context;
    }
}
