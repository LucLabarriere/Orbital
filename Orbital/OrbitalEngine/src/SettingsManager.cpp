#include "OrbitalEngine/SettingsManager.h"
#include "OrbitalRenderer/Window.h"
#include "OrbitalTools/Errors.h"

namespace Orbital
{
	SettingsManager::SettingsManager() : mSettings()
	{
		mSettings.reserve((size_t)Setting::SIZE);

		mSettings.emplace_back(800u);					// WindowWidth
		mSettings.emplace_back(600u);					// WindowHeight
		mSettings.emplace_back(60.0f);					// FOV
		mSettings.emplace_back(Window::Mode::Windowed); // WindowMode
		mSettings.emplace_back(true);					// VSync
		mSettings.emplace_back(true);					// MouseVisible
		mSettings.emplace_back(std::string("Orbital")); // WindowTitle

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