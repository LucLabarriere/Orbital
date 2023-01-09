#pragma once
#include "OrbitalEngine/Context.h"

namespace Orbital
{
	enum class Setting
	{
		WindowWidth = 0,
		WindowHeight,
		FOV,
		WindowMode,
		VSync,
		MouseVisible,
		WindowTitle,
		WorldUp,
		MouseSensitivity,
		SIZE,
	};

	static std::string SettingNames[(size_t)Setting::SIZE] = {
		"Window width", "Window height", "FOV", "Window mode", "VSync", "Mouse visible", "Window title", "World Up", "MouseSensitivity",
	};
	static_assert(sizeof(SettingNames) / sizeof(std::string) == (size_t)Setting::SIZE);
} // namespace Orbital
