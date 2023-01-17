#include "DemoLibrary/Application.h"
#include "DemoLibrary/Components.h"
#include "DemoLibrary/DemoScene.h"
#include "OrbitalEngine/ScriptsLibraryLoader.h"
#include "OrbitalEngine/Settings.h"

#include "DemoScripts/CoreScript.h"

namespace Demo
{
	Application::Application() : OrbitalApplication()
	{
	}

	void Application::onInitialize()
	{
		mServices.ScriptEngine.RegisterLibrary("Demo-Scripts");

		mServices.ScriptEngine.RegisterScript("Demo-Scripts", "PlayerController");
		mServices.ScriptEngine.RegisterScript("Demo-Scripts", "ProjectileScript");
		mServices.ScriptEngine.RegisterScript("Demo-Scripts", "CoreScript");
		mServices.ScriptEngine.RegisterScript("Demo-Scripts", "EnemyScript");
		mServices.ScriptEngine.RegisterScript("Demo-Scripts", "WeaponPickup");

		mServices.ScriptEngine.LoadLibraries();

		mServices.Settings.GetMut<std::string>(Setting::WindowTitle) = "Demo";

		// Initialize the main scene of the demo application;
		changeScene<DemoScene>();
	}
} // namespace Demo
