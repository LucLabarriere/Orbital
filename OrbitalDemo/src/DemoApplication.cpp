#include "OrbitalDemo/DemoApplication.h"
#include "OrbitalEngine/ECS/Components.h"
#include "OrbitalScripts/CoreDemoApplication.h"
#include "OrbitalScripts/Components/Components.h"

namespace Orbital
{
	DemoApplication::DemoApplication() : OrbitalApplication()
	{
	}

	void DemoApplication::initialize()
	{
		OrbitalApplication::initialize();
	}

	void DemoApplication::terminate()
	{
		OrbitalApplication::terminate();
	}

	void DemoApplication::initializeComponents()
	{
		mServices.ECS.RegisterComponentType<Health>();
		mServices.ScriptEngine.RegisterScript("CoreDemoApplication");
		mServices.ScriptEngine.RegisterScript("PlayerController");
		mServices.ScriptEngine.RegisterScript("SpawnEnemies");
		mServices.ScriptEngine.RegisterScript("EnemyScript");
		mServices.ScriptEngine.RegisterScript("WeaponPickup");
		mServices.ScriptEngine.RegisterScript("ProjectileScript");
	}

	void DemoApplication::onLoad()
	{
		Logger::Debug("Loading Demo Application");

		auto e = mServices.ECS.CreateEntity();
		e.push<CoreDemoApplication>();

		Logger::Debug("Done loading Demo application");
	}

	void DemoApplication::preUpdate(const Time& dt)
	{
		OrbitalApplication::preUpdate(dt);
	}

	void DemoApplication::update(const Time& dt)
	{
		OrbitalApplication::update(dt);
	}

	bool DemoApplication::onKeyPressed(KeyPressedEvent& e)
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
} // namespace Orbital
