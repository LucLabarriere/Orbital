#include "OrbitalEngine/SettingManager.h"
#include "OrbitalEngine/Settings.h"
#include "OrbitalRenderer/Window.h"
#include "OrbitalTools/Errors.h"

namespace Orbital
{
	SettingManager::SettingManager()
	{
		mSettings[(size_t)Setting::WindowWidth] = 800u;
		mSettings[(size_t)Setting::WindowHeight] = 600u;
		mSettings[(size_t)Setting::FOV] = 60.0f;
		mSettings[(size_t)Setting::WindowMode] = Window::Mode::Windowed;
		mSettings[(size_t)Setting::VSync] = true;
		mSettings[(size_t)Setting::MouseVisible] = true;
		mSettings[(size_t)Setting::WindowTitle] = std::string_view("Orbital");
		mSettings[(size_t)Setting::WorldUp] = Maths::Vec3(0.0f, 1.0f, 0.0f);
		mSettings[(size_t)Setting::MouseSensitivity] = 100.0f;

		for (size_t i = 0; i < (size_t)Setting::SIZE; i++)
			mCallbacks.emplace_back([]() {});
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
