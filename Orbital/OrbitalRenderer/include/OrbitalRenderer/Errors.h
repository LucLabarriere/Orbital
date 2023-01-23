#pragma once

#include "OrbitalTools/Errors.h"

namespace Orbital
{
	enum class RendererError : int
	{
		WindowCreation = 1 << 1,
		GLFWinit = 2 << 1,
		OpenGLLoad = 3 << 1,
		OpenGLinit = 4 << 1
	};
} // namespace Orbital
