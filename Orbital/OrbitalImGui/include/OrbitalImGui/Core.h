#pragma once
#include "OrbitalImGui/Context.h"
#include "OrbitalTools/Pointers.h"

namespace Orbital
{
	class Window;

	namespace Gui
	{
		void InitializeImGui(UniqueHandle<Window> window);
		void BeginFrame();
		void EndFrame();
		void TerminateImGui();
		auto CapturingMouseEvents() -> bool;
		auto CapturingKeyboardEvents() -> bool;
	} // namespace Gui
} // namespace Orbital
