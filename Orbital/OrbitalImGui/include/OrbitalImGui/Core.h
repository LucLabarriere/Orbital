#pragma once

#include "OrbitalImGui/Context.h"
#include "OrbitalTools/Pointers.h"

namespace Orbital
{
	class Window;

	namespace Gui
	{
		auto InitializeImGui(UniqueHandle<Window> window) -> void;
		auto BeginFrame() -> void;
		auto EndFrame() -> void;
		auto TerminateImGui() -> void;
		auto CapturingMouseEvents() -> bool;
		auto CapturingKeyboardEvents() -> bool;
	} // namespace Gui
} // namespace Orbital
