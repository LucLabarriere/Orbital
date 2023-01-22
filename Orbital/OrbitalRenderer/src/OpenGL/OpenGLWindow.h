#pragma once
#include "OrbitalRenderer/RendererContext.h"
#include "OrbitalRenderer/Window.h"

namespace Orbital
{
	class ORBITAL_RENDERER_API OpenGLWindow : public Window
	{
	public:
		OpenGLWindow() = default;
		~OpenGLWindow() override = default;

		void swapBuffers() const override;
		auto initialize(unsigned int windowWidth, unsigned int windowHeight)
			-> Option<Error> override;
		auto getNativeWindow() -> void* override;
		[[nodiscard]] auto shouldClose() const -> bool override;
		void resize(unsigned int w, unsigned int h) override;
		void setVSync(bool value) override;
		void setWindowMode(Window::Mode value) override;
		void setMouseEnabled(bool value) override;
		void setTitle(std::string_view title) override;

	private:
		GLFWwindow* mGLFWwindow = nullptr;
	};
} // namespace Orbital
