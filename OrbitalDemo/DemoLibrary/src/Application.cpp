#include "DemoLibrary/Application.h"
#include "DemoLibrary/Components.h"
#include "DemoLibrary/MainScene.h"
#include "OrbitalEngine/ScriptsLibraryLoader.h"

#include "DemoScripts/CoreScript.h"

namespace Demo
{
	Application::Application() : OrbitalApplication()
	{
	}

	void Application::initialize()
	{
		OrbitalApplication::initialize();

		mServices.ScriptEngine.RegisterLibrary("DemoScripts");

		mServices.ScriptEngine.RegisterScript("DemoScripts", "PlayerController");
		mServices.ScriptEngine.RegisterScript("DemoScripts", "ProjectileScript");
		mServices.ScriptEngine.RegisterScript("DemoScripts", "CoreScript");
		mServices.ScriptEngine.RegisterScript("DemoScripts", "EnemyScript");
		mServices.ScriptEngine.RegisterScript("DemoScripts", "WeaponPickup");

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

		return true;
	}
} // namespace Demo
