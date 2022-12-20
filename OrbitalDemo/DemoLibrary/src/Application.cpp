#include "DemoLibrary/Application.h"
#include "DemoLibrary/Components.h"
#include "DemoLibrary/MainScene.h"

#include "DemoScripts/CoreScript.h"

namespace Demo
{
	Application::Application() : OrbitalApplication()
	{
	}

	void Application::initialize()
	{
		OrbitalApplication::initialize();

		mServices.ScriptEngine.SetLibrary("DemoScripts");
		mServices.ScriptEngine.Reload();
		mServices.ScriptEngine.RegisterScript("PlayerController");
		mServices.ScriptEngine.RegisterScript("ProjectileScript");
		mServices.ScriptEngine.RegisterScript("CoreScript");
		mServices.ScriptEngine.RegisterScript("EnemyScript");
		mServices.ScriptEngine.RegisterScript("WeaponPickup");

		// Initialize the main scene of the demo application;
		loadScene<MainScene>();
	}

	bool Application::onKeyPressed(KeyPressedEvent& e)
	{
		if (e.getKey() == OE_KEY_F2)
		{
			Logger::Log("Reloading scripts");
			mServices.ECS.Reset();

			bool compilationSucceeded = mServices.ScriptEngine.Reload();

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

		return true;
	}
} // namespace Demo
