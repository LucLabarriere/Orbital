#include "OrbitalEditor/EditorApplication.h"
#include "OrbitalEngine/Components.h"

namespace Orbital
{
	EditorApplication::EditorApplication() : OrbitalApplication()
	{
	}

	void EditorApplication::initialize()
	{
		OrbitalApplication::initialize();
		initializeScripts();
	}

	void EditorApplication::terminate()
	{
		OrbitalApplication::terminate();
	}

	void EditorApplication::onLoad()
	{
		Logger::Debug("Loading Editor Application");

		auto e = mServices.ECS.CreateEntity();
		auto manager = e.get<NativeScriptManager>();
		manager->push("CoreEditorApplication", e);

		Logger::Debug("Done loading Editor application");
	}

	void EditorApplication::update(const Time& dt)
	{
		OrbitalApplication::update(dt);
	}

	bool EditorApplication::onKeyPressed(KeyPressedEvent& e)
	{
		if (e.getKey() == OE_KEY_ESCAPE)
		{
			Logger::Log("Reloading scripts");
			mServices.Physics.ResetCollisionSolvers(); // Necessary otherwise it crashes
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

		size_t steps = mServices.Physics.GetVerletSteps();

		if (e.getKey() == OE_KEY_UP && steps <= 10000)
		{
			mServices.Physics.SetVerletSteps(steps + 10);
		}

		else if (e.getKey() == OE_KEY_DOWN && steps > 11)
		{
			mServices.Physics.SetVerletSteps(steps - 10);
		}

		return true;
	}

	void EditorApplication::initializeScripts()
	{
		mServices.ScriptEngine.RegisterScript("CoreEditorApplication");
		mServices.ScriptEngine.RegisterScript("PlayerController");
	}
} // namespace Orbital
