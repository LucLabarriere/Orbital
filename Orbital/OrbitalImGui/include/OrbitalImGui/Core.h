#pragma once
#include "OrbitalImGui/Context.h"

namespace Orbital
{
	class Window;

	namespace Gui
	{
		void InitializeImGui(Window* window);
		void BeginFrame();
		void EndFrame();
		void TerminateImGui();
		bool CapturingMouseEvents();
		bool CapturingKeyboardEvents();
	} // namespace Gui
} // namespace Orbital
