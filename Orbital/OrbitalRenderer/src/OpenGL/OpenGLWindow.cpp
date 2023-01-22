#include "OpenGL/OpenGLWindow.h"
#include "OrbitalRenderer/Errors.h"
#include "OrbitalRenderer/RenderAPI.h"
#include "OrbitalTools/Logger.h"

namespace Orbital
{
	auto Window::Create(unsigned int windowWidth, unsigned int windowHeight)
		-> Expected<Unique<Window>, Error>
	{
		auto window = MakeUnique<OpenGLWindow>();
		auto error = window->initialize(windowWidth, windowHeight);
		if (error.has_value()) return MakeUnexpected(error.value());

		return std::move(window);
	}

	void OpenGLWindow::swapBuffers() const
	{
		glfwSwapBuffers(mGLFWwindow);
	}

	auto OpenGLWindow::initialize(unsigned int windowWidth, unsigned int windowHeight)
		-> Option<Error>
	{
		mGLFWwindow =
			glfwCreateWindow(windowWidth, windowHeight, "Orbital", nullptr, nullptr);

		if (!mGLFWwindow)
		{
			glfwTerminate();
			return Error{ .type = (int)RendererError::WindowCreation,
						  .message = "Could not create the GLFW window" };
		}

		glfwMakeContextCurrent(mGLFWwindow);

		return {};
	}

	void OpenGLWindow::resize(unsigned int w, unsigned int h)
	{
		glfwSetWindowSize(mGLFWwindow, (int)w, (int)h);
	}

	auto OpenGLWindow::getNativeWindow() -> void*
	{
		return (void*)mGLFWwindow;
	}

	auto OpenGLWindow::shouldClose() const -> bool
	{
		return glfwWindowShouldClose(mGLFWwindow);
	}

	void OpenGLWindow::setVSync(bool value)
	{
		// const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		glfwSwapInterval((int)!value);
	}

	void OpenGLWindow::setWindowMode(Window::Mode value)
	{
		switch (value)
		{
		case Window::Mode::FullScreen:
		{
			int w, h = 0;
			glfwGetWindowSize(mGLFWwindow, &w, &h);

			const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

			glfwSetWindowMonitor(
				mGLFWwindow, glfwGetPrimaryMonitor(), 0, 0, w, h, mode->refreshRate
			);
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
		glfwSetInputMode(
			mGLFWwindow, GLFW_CURSOR, (value) ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED
		);
	}

	void OpenGLWindow::setTitle(std::string_view title)
	{
		glfwSetWindowTitle(mGLFWwindow, title.data());
	}
} // namespace Orbital
