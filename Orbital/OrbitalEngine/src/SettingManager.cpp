#include "OrbitalEngine/SettingManager.h"
#include "OrbitalEngine/Settings.h"
#include "OrbitalRenderer/Window.h"
#include "OrbitalTools/Errors.h"

namespace Orbital
{
	SettingManager::SettingManager() : mSettings()
	{
		mSettings.reserve((size_t)Setting::SIZE);

		mSettings.emplace_back(800u);						   // WindowWidth
		mSettings.emplace_back(600u);						   // WindowHeight
		mSettings.emplace_back(60.0f);						   // FOV
		mSettings.emplace_back(Window::Mode::Windowed);		   // WindowMode
		mSettings.emplace_back(true);						   // VSync
		mSettings.emplace_back(true);						   // MouseVisible
		mSettings.emplace_back(std::string("Orbital"));		   // WindowTitle
		mSettings.emplace_back(Maths::Vec3(0.0f, 1.0f, 0.0f)); // WorldUp;
		mSettings.emplace_back(100.0f);						   // MouseSensitivity

		for (size_t i = 0; i < (size_t)Setting::SIZE; i++)
			mCallbacks.emplace_back([]() {});

		Orbital::Assert(mSettings.size() == (size_t)Setting::SIZE, "The settings were not properly initialized");
	}

	void SettingManager::handleCallbacks()
	{
		for (auto& setting : mRequestedCallbacks)
		{
			mCallbacks[(size_t)setting]();
		}

		mRequestedCallbacks.clear();
	}
} // namespace Orbital
