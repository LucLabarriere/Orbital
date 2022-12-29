#include "OrbitalEngine/SettingsManager.h"
#include "OrbitalRenderer/Window.h"

namespace Orbital
{
	SettingsManager::SettingsManager() : mSettings()
	{
		mSettings.reserve((size_t)Setting::SIZE);

		mSettings.emplace_back(800u);  // WINDOWWIDTH
		mSettings.emplace_back(600u);  // WINDOWHEIGHT
		mSettings.emplace_back(60.0f); // FOV
		mSettings.emplace_back(Window::Mode::Windowed);  // WINDOWMODE
		mSettings.emplace_back(true);  // VSYNC
		mSettings.emplace_back(0u);	   // FPSLimit
		mSettings.emplace_back(true);  // MouseVisible

		for (size_t i = 0; i < (size_t)Setting::SIZE; i++)
			mCallbacks.emplace_back([]() {});

		Orbital::Assert(mSettings.size() == (size_t)Setting::SIZE, "The settings were not properly initialized");
	}

	void SettingsManager::handleCallbacks()
	{
		for (auto& setting : mRequestedCallbacks)
		{
			mCallbacks[(size_t)setting]();
		}

		mRequestedCallbacks.clear();
	}
} // namespace Orbital
