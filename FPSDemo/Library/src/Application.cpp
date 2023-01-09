#include "FPSDemoLibrary/Application.h"
#include "FPSDemoLibrary/Components.h"
#include "FPSDemoLibrary/FPSDemoScene.h"
#include "OrbitalEngine/ScriptsLibraryLoader.h"
#include "OrbitalEngine/Settings.h"

#include "FPSDemoScripts/CoreScript.h"

namespace FPSDemo
{
	Application::Application() : OrbitalApplication()
	{
	}

	void Application::initialize()
	{
		OrbitalApplication::initialize();

		mServices.ScriptEngine.RegisterLibrary("FPSDemo-Scripts");

		mServices.ScriptEngine.RegisterScript("FPSDemo-Scripts", "PlayerController");
		mServices.ScriptEngine.RegisterScript("FPSDemo-Scripts", "ProjectileScript");
		mServices.ScriptEngine.RegisterScript("FPSDemo-Scripts", "CoreScript");
		mServices.ScriptEngine.RegisterScript("FPSDemo-Scripts", "EnemyScript");
		mServices.ScriptEngine.RegisterScript("FPSDemo-Scripts", "WeaponPickup");

		mServices.ScriptEngine.LoadLibraries();

		mServices.Settings.GetMut<std::string>(Setting::WindowTitle) = "FPSDemo";

		// Initialize the main scene of the demo application;
		loadScene<FPSDemoScene>();
	}
} // namespace FPSDemo
