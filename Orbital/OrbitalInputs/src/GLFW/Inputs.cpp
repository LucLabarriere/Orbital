#include "OrbitalInputs/Inputs.h"
#include "OrbitalInputs/Context.h"

namespace Orbital
{
	static Maths::Vec2 sFormerMousePosition(0.0f, 0.0f);
	static Maths::Vec2 sCurrentMousePosition(0.0f, 0.0f);
	static Maths::Vec2 sMouseDrag(0.0f, 0.0f);

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

	Maths::Vec2 Inputs::GetMouseDrag()
	{
		return sMouseDrag;
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

	void Inputs::UpdateDrag()
	{
		sCurrentMousePosition = Inputs::GetScreenSpaceMousePosition();
		sMouseDrag = sFormerMousePosition - sCurrentMousePosition;
		sFormerMousePosition = sCurrentMousePosition;
	}
} // namespace Orbital
