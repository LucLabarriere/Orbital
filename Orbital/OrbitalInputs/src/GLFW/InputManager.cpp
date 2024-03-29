#include "OrbitalInputs/InputManager.h"
#include "OrbitalInputs/Event.h"
#include "OrbitalInputs/Inputs.h"

namespace Orbital
{
	void InputManager::initializeInputManager(void* context)
	{
		GLFWwindow* window = (GLFWwindow*)context;
		Inputs::SetContext(context);

		glfwSetWindowUserPointer(window, this);

		// KEYBOARD
		glfwSetKeyCallback(
			window,
			[](GLFWwindow* w, int key, int scanCode, int action, int mods)
			{
				auto manager = (InputManager*)glfwGetWindowUserPointer(w);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent e(key);
					manager->onEvent(e);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent e(key);
					manager->onEvent(e);
					break;
				}
				case GLFW_REPEAT:
					KeyPressedEvent e(key);
					manager->onEvent(e);
					break;
				}
			}
		);

		// MOUSE
		// TODO
		// Check for raw motion, it might be better
		// Add cursor enter callback
		glfwSetCursorPosCallback(
			window,
			[](GLFWwindow* w, double xPos, double yPos)
			{
				auto manager = (InputManager*)glfwGetWindowUserPointer(w);

				MouseMoveEvent e((float)xPos, (float)yPos);
				manager->onEvent(e);
			}
		);

		glfwSetMouseButtonCallback(
			window,
			[](GLFWwindow* w, int button, int action, int mods)
			{
				auto manager = (InputManager*)glfwGetWindowUserPointer(w);

				double xPos, yPos;
				glfwGetCursorPos(w, &xPos, &yPos);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent e(xPos, (float)yPos, button);
					manager->onEvent(e);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent e((float)xPos, (float)yPos, button);
					manager->onEvent(e);
					break;
				}
				}
			}
		);

		glfwSetScrollCallback(
			window,
			[](GLFWwindow* w, double xOffset, double yOffset)
			{
				auto manager = (InputManager*)glfwGetWindowUserPointer(w);

				double xPos, yPos;
				glfwGetCursorPos(w, &xPos, &yPos);

				MouseScrolledEvent e(
					(float)xPos, (float)yPos, (float)xOffset, (float)yOffset
				);
				manager->onEvent(e);
			}
		);

		EventSlot<KeyPressedEvent>::Connect(
			std::bind(&InputManager::onKeyPressed, this, std::placeholders::_1)
		);
		EventSlot<KeyReleasedEvent>::Connect(
			std::bind(&InputManager::onKeyReleased, this, std::placeholders::_1)
		);
		EventSlot<MouseMoveEvent>::Connect(
			std::bind(&InputManager::onMouseMove, this, std::placeholders::_1)
		);
		EventSlot<MouseButtonPressedEvent>::Connect(
			std::bind(&InputManager::onMouseButtonPressed, this, std::placeholders::_1)
		);
		EventSlot<MouseButtonReleasedEvent>::Connect(
			std::bind(&InputManager::onMouseButtonReleased, this, std::placeholders::_1)
		);
		EventSlot<MouseScrolledEvent>::Connect(
			std::bind(&InputManager::onMouseScrolled, this, std::placeholders::_1)
		);
	}

	void InputManager::pollEvents()
	{
		glfwPollEvents();
	}
} // namespace Orbital
