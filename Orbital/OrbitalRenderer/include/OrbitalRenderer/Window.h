#pragma once
#include "Context.h"
#include "OrbitalTools/Errors.h"
#include "OrbitalTools/Pointers.h"

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

		virtual ~Window() = default;
		static auto Create(unsigned int windowWidth, unsigned int windowHeight)
			-> Expected<Unique<Window>, Error>;

		virtual void swapBuffers() const = 0;
		virtual auto initialize(unsigned int windowWidth, unsigned int windowHeight)
			-> Option<Error> = 0;
		virtual auto getNativeWindow() -> void* = 0;
		[[nodiscard]] virtual auto shouldClose() const -> bool = 0;
		virtual void resize(unsigned int w, unsigned int h) = 0;
		virtual void setVSync(bool value) = 0;
		virtual void setWindowMode(Window::Mode value) = 0;
		virtual void setMouseEnabled(bool value) = 0;
		virtual void setTitle(std::string_view title) = 0;
	};
} // namespace Orbital
