#include "OrbitalInputs/Inputs.h"
#include "OrbitalInputs/Context.h"

namespace Orbital
{
	Maths::Vec2 Inputs::GetMousePosition()
	{
		double xPos, yPos;
		glfwGetCursorPos(static_cast<GLFWwindow*>(mContext), &xPos, &yPos);
		return Maths::Vec2((float)xPos, (float)yPos);
	}

	Maths::Vec2 Inputs::GetScreenSpaceMousePosition()
	{
		Maths::Vec2 target = GetMousePosition();
		target.x /= 640.0f;
		target.y /= 480.0f;
		target = target * 2.0f - 1.0f;
		target.y = -target.y;

		return target;
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
} // namespace Orbital
