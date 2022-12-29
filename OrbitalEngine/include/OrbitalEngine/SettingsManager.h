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
		FPSLimit,
		MouseVisible,
		SIZE,
	};

	static const char* SettingNames[(size_t)Setting::SIZE] = {
		"Window width", "Window height", "FOV", "Window mode", "VSync", "FPS limit", "Mouse visible",
	};
	static_assert(sizeof(SettingNames) / sizeof(const char*) == (size_t)Setting::SIZE);

	class OENGINE_API SettingsManager
	{
	public:
		SettingsManager();

		template <typename T>
		T& getMut(Setting setting)
		{
			std::any& s = mSettings[(size_t)setting];
			Orbital::Assert(s.type() == typeid(T), "The setting was accessed using the incorrect type");
			mRequestedCallbacks.emplace(setting);
			return std::any_cast<T&>(s);
		}

		template <typename T>
		const T& get(Setting setting) const
		{
			const std::any& s = mSettings[(size_t)setting];
			Orbital::Assert(s.type() == typeid(T), "The setting was accessed using the incorrect type");
			return std::any_cast<const T&>(s);
		}

		void setCallback(Setting setting, const std::function<void()>& callback)
		{
			mCallbacks[(size_t)setting] = callback;
		}

		void handleCallbacks();

	private:
		std::vector<std::any> mSettings;
		std::vector<std::function<void()>> mCallbacks;
		std::unordered_set<Setting> mRequestedCallbacks;
	};
} // namespace Orbital
