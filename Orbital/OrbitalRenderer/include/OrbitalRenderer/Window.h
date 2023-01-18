#pragma once
#include "Context.h"

namespace Orbital
{
	class ORBITAL_RENDERER_API Window
	{
	public:
		enum class Mode
		{
			FullScreen,
			Windowed,
			Borderless,
		};

		virtual ~Window(){};
		static Window* Create();

		virtual void swapBuffers() const = 0;
		virtual bool initialize(unsigned int windowWidth, unsigned int windowHeight) = 0;
		virtual auto getNativeWindow() -> void* = 0;
		virtual bool shouldClose() const = 0;
		virtual void resize(unsigned int w, unsigned int h) = 0;
		virtual void setVSync(bool value) = 0;
		virtual void setWindowMode(Window::Mode value) = 0;
		virtual void setMouseEnabled(bool value) = 0;
		virtual void setTitle(const std::string& title) = 0;
	};
} // namespace Orbital
