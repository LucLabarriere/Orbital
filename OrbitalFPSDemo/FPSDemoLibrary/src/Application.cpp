#include "FPSDemoLibrary/Application.h"
#include "FPSDemoLibrary/Components.h"
#include "FPSDemoLibrary/MainScene.h"
#include "OrbitalEngine/ScriptsLibraryLoader.h"

#include "FPSDemoScripts/CoreScript.h"

namespace FPSDemo
{
	Application::Application() : OrbitalApplication()
	{
	}

	void Application::initialize()
	{
		OrbitalApplication::initialize();

		mServices.ScriptEngine.RegisterLibrary("FPSDemoScripts");

		mServices.ScriptEngine.RegisterScript("FPSDemoScripts", "PlayerController");
		mServices.ScriptEngine.RegisterScript("FPSDemoScripts", "ProjectileScript");
		mServices.ScriptEngine.RegisterScript("FPSDemoScripts", "CoreScript");
		mServices.ScriptEngine.RegisterScript("FPSDemoScripts", "EnemyScript");
		mServices.ScriptEngine.RegisterScript("FPSDemoScripts", "WeaponPickup");

		mServices.ScriptEngine.LoadLibraries();

		// Initialize the main scene of the demo application;
		loadScene<MainScene>();
	}

	bool Application::onKeyPressed(KeyPressedEvent& e)
	{
		if (e.getKey() == OE_KEY_F2)
		{
			Logger::Log("Reloading scripts");
			mServices.ECS.Reset();

			bool compilationSucceeded = mServices.ScriptEngine.Recompile();

			if (compilationSucceeded)
			{
				onLoad(); // Initializing application specific stuff
				mServices.Scenes.OnLoad();
				mServices.Scenes.OnStart();
			}

			Logger::Trace("Done reloading scripts");
		}

		// size_t steps = mServices.Physics.GetVerletSteps();
		size_t steps = 0;

		if (e.getKey() == OE_KEY_UP && steps <= 10000)
		{
			// mServices.Physics.SetVerletSteps(steps + 10);
		}

		else if (e.getKey() == OE_KEY_DOWN && steps > 11)
		{
			// mServices.Physics.SetVerletSteps(steps - 10);
		}

		else if (e.getKey() == OE_KEY_ESCAPE)
		{
			requestExit();
		}

		else if (e.getKey() == OE_KEY_F3)
		{
			auto& windowMode = mServices.Settings.GetMut<Window::Mode>(Setting::WindowMode);

			switch (windowMode)
			{
			case Window::Mode::FullScreen:
			{
				windowMode = Window::Mode::Windowed;
				break;
			}
			case Window::Mode::Windowed:
			{
				windowMode = Window::Mode::FullScreen;
				break;
			}
			case Window::Mode::Borderless:
			{
				windowMode = Window::Mode::Windowed;
				break;
			}
			}
		}

		else if (e.getKey() == OE_KEY_F4)
		{
			bool& vsync = mServices.Settings.GetMut<bool>(Setting::VSync);
			vsync = !vsync;
		}
		return true;
	}
} // namespace FPSDemo
