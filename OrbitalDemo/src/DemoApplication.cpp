#include "OrbitalDemo/DemoApplication.h"
#include "OrbitalDemo/MainScene.h"
#include "OrbitalEngine/ECS/Components.h"
#include "OrbitalScripts/Components/Components.h"
#include "OrbitalScripts/CoreDemoApplication.h"

DemoApplication::DemoApplication() : OrbitalApplication()
{
}

void DemoApplication::initialize()
{
	OrbitalApplication::initialize();

	// Initialize the main scene of the demo application;
	Logger::Debug("Initializing MainScene");
	loadScene<MainScene>();
}

void DemoApplication::terminate()
{
	OrbitalApplication::terminate();
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
