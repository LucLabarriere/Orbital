#pragma once
#include "OrbitalRenderer/RendererContext.h"
#include "OrbitalRenderer/Window.h"

namespace Orbital
{
	class ORENDERER_API OpenGLWindow : public Window
	{
	public:
		OpenGLWindow();
		virtual ~OpenGLWindow() override{};

		virtual void swapBuffers() const override;
		virtual bool initialize(unsigned int windowWidth, unsigned int windowHeight) override;
		virtual void* getNativeWindow() override;
		virtual bool shouldClose() const override;
		virtual void resize(unsigned int w, unsigned int h) override;
		virtual void setVSync(bool value) override;
		virtual void setWindowMode(Window::Mode value) override;
		virtual void setMouseEnabled(bool value) override;

	private:
		GLFWwindow* mGLFWwindow = nullptr;
	};
} // namespace Orbital
