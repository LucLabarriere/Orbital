#include "OrbitalInputs/Inputs.h"
#include "OrbitalInputs/Context.h"

namespace Orbital
{
	static Maths::Vec2 sFormerMousePosition(0.0f, 0.0f);
	static Maths::Vec2 sCurrentMousePosition(0.0f, 0.0f);
	static Maths::Vec2 sMouseDrag(0.0f, 0.0f);
	static bool sRegisteringMouseEvents = true;
	static bool sRegisteringKeyboardEvents = true;

	auto Inputs::GetMousePosition() -> Maths::Vec2
	{
		double xPos, yPos;
		glfwGetCursorPos(static_cast<GLFWwindow*>(mContext), &xPos, &yPos);
		return Maths::Vec2((float)xPos, (float)yPos);
	}

	auto Inputs::GetScreenSpaceMousePosition() -> Maths::Vec2
	{
		Maths::Vec2 target = GetMousePosition();
		target.x /= 640.0f;
		target.y /= 480.0f;
		target = target * 2.0f - 1.0f;
		target.y = -target.y;

		return target;
	}

	auto Inputs::GetMouseDrag() -> Maths::Vec2
	{
		return sMouseDrag;
	}

	auto Inputs::IsKeyDown(int key) -> bool
	{
		if (!sRegisteringKeyboardEvents) return false;
		return glfwGetKey(static_cast<GLFWwindow*>(mContext), key) == GLFW_PRESS ? true
																				 : false;
	}

	auto Inputs::IsMouseButtonDown(int button) -> bool
	{
		if (!sRegisteringMouseEvents) return false;
		return glfwGetMouseButton(static_cast<GLFWwindow*>(mContext), button) ==
					   GLFW_PRESS
				   ? true
				   : false;
	}

	void Inputs::SetContext(void* context)
	{
		mContext = context;
	}

	void Inputs::RegisterMouseEvents(bool value)
	{
		sRegisteringMouseEvents = value;
	}

	void Inputs::RegisterKeyboardEvents(bool value)
	{
		sRegisteringKeyboardEvents = value;
	}

	void Inputs::UpdateDrag()
	{
		sCurrentMousePosition = Inputs::GetScreenSpaceMousePosition();
		sMouseDrag = sFormerMousePosition - sCurrentMousePosition;
		sFormerMousePosition = sCurrentMousePosition;
	}
} // namespace Orbital
