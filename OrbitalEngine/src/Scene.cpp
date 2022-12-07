#include "OrbitalEngine/Scene.h"
#include "OrbitalEngine/ECS/Components/NativeScriptManager.h"
#include "OrbitalEngine/ScriptsLibraryLoader.h"

namespace Orbital
{
	Scene::Scene(const SharedApplication& app) : SceneServices(app), mManager(new ECSManager)
	{
		SceneServices::InitializeServices();
	}

	void Scene::terminate()
	{
		LOGFUNC();
		mManager->cleanUp();
		Logger::Debug("Deleting ECS Registry");
		mManager.reset();
	}

	void Scene::reset()
	{
		mManager->reset();
	}

	Entity Scene::createEntity()
	{
		Entity e = mManager->createEntity();
		e.push<NativeScriptManager>(mApp);
		return e;
	}

	void Scene::onLoad()
	{
		for (auto& [uuid, manager] : mManager->components<NativeScriptManager>())
		{
			manager.onLoad();
		}
	}

	void Scene::onStart()
	{
		for (auto& [uuid, manager] : mManager->components<NativeScriptManager>())
		{
			manager.onStart();
		}
	}

	void Scene::onUpdate(const Time& dt)
	{
		if (ScriptEngine.LastCompilationSucceeded())
		{
			for (auto& [uuid, manager] : mManager->components<NativeScriptManager>())
			{
				manager.onUpdate(dt);
			}
		}
	}

	void Scene::onCleanUp()
	{
		for (auto& [uuid, manager] : mManager->components<NativeScriptManager>())
		{
			manager.onCleanUp();
		}

		mManager->reset();
	}
} // namespace Orbital
