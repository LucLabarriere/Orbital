#include "OrbitalEngine/Scene.h"
#include "OrbitalEngine/Components/NativeScriptManager.h"
#include "OrbitalEngine/ScriptsLibraryLoader.h"

namespace Orbital
{
	Scene::Scene(const SharedApplication& app) : SceneServices(app), mRegistry(new ECS::Registry)
	{
		SceneServices::InitializeServices();
	}

	void Scene::terminate()
	{
		LOGFUNC();
		mRegistry->cleanUp();
		Logger::Debug("Deleting ECS Registry");
		delete mRegistry;
	}

	void Scene::reset()
	{
		mRegistry->reset();
	}

	Entity Scene::createEntity()
	{
		Entity e(mRegistry->createEntity());
		e.push<NativeScriptManager>(mApp);
		return e;
	}

	void Scene::onLoad()
	{
		for (auto& [uuid, manager] : mRegistry->components<NativeScriptManager>())
		{
			manager.onLoad();
		}
	}

	void Scene::onStart()
	{
		for (auto& [uuid, manager] : mRegistry->components<NativeScriptManager>())
		{
			manager.onStart();
		}
	}

	void Scene::onUpdate(const Time& dt)
	{
		if (ScriptEngine.LastCompilationSucceeded())
		{
			for (auto& [uuid, manager] : mRegistry->components<NativeScriptManager>())
			{
				manager.onUpdate(dt);
			}
		}
	}

	void Scene::onCleanUp()
	{
		for (auto& [uuid, manager] : mRegistry->components<NativeScriptManager>())
		{
			manager.onCleanUp();
		}

		mRegistry->reset();
	}
} // namespace Orbital
