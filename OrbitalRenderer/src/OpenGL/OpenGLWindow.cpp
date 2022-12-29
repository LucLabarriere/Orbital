#include "OpenGL/OpenGLWindow.h"
#include "OrbitalRenderer/RenderAPI.h"
#include "OrbitalTools/Errors.h"
#include "OrbitalTools/Logger.h"

namespace Orbital
{
	Window* Window::Create()
	{
		return new OpenGLWindow;
	}

	OpenGLWindow::OpenGLWindow()
	{
	}

	void OpenGLWindow::swapBuffers() const
	{
		glfwSwapBuffers(mGLFWwindow);
	}

	bool OpenGLWindow::initialize(unsigned int windowWidth, unsigned int windowHeight)
	{
		Orbital::Logger::Log("Creating the window");

		mGLFWwindow = glfwCreateWindow(windowWidth, windowHeight, "Orbital", NULL, NULL);

		if (!mGLFWwindow)
		{
			Orbital::Logger::Critical("Error while creating the GLFW window");
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(mGLFWwindow);

		return true;
	}

	void OpenGLWindow::resize(unsigned int w, unsigned int h)
	{
		glfwSetWindowSize(mGLFWwindow, (int)w, (int)h);
	}

	void* OpenGLWindow::getNativeWindow()
	{
		return (void*)mGLFWwindow;
	}

	bool OpenGLWindow::shouldClose() const
	{
		return glfwWindowShouldClose(mGLFWwindow);
	}

	void OpenGLWindow::setVSync(bool value)
	{
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		glfwSwapInterval(value ? mode->refreshRate: 0);
	}

	void OpenGLWindow::setWindowMode(Window::Mode value)
	{
		switch (value)
		{
		case Window::Mode::FullScreen:
		{
			int w, h, r = 0;
			glfwGetWindowSize(mGLFWwindow, &w, &h);

			const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

			glfwSetWindowMonitor(mGLFWwindow, glfwGetPrimaryMonitor(), 0, 0, w, h, mode->refreshRate);
			break;
		}
		case Window::Mode::Windowed:
		{
			int w, h = 0;
			glfwGetWindowSize(mGLFWwindow, &w, &h);

			const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

			glfwSetWindowMonitor(mGLFWwindow, nullptr, 0, 0, w, h, mode->refreshRate);
			break;
		}
		case Window::Mode::Borderless:
		{
			Orbital::Raise("Not implemented");
			break;
		}
		}
	}

	void OpenGLWindow::setMouseEnabled(bool value)
	{
		glfwSetInputMode(mGLFWwindow, GLFW_CURSOR, (value) ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
	}
} // namespace Orbital
