#include "OpenGL/OpenGLWindow.h"
#include "OrbitalLogger/Logger.h"
#include "OrbitalRenderer/RenderAPI.h"

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

	bool OpenGLWindow::initialize()
	{
		Orbital::Logger::Log("Creating the window");

		mGLFWwindow = glfwCreateWindow(640, 480, "Orbital", NULL, NULL);

		if (!mGLFWwindow)
		{
			Orbital::Logger::Critical("Error while creating the GLFW window");
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(mGLFWwindow);

		return true;
	}

	void* OpenGLWindow::getNativeWindow()
	{
		return (void*)mGLFWwindow;
	}

	bool OpenGLWindow::shouldClose() const
	{
		return glfwWindowShouldClose(mGLFWwindow);
	}
} // namespace Orbital
