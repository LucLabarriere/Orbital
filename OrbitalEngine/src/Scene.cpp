#include "OrbitalEngine/Scene.h"
#include "OrbitalEngine/ECS/Components/NativeScriptManager.h"
#include "OrbitalEngine/ScriptsLibraryLoader.h"

#include "OrbitalEngine/ECS/Components.h"

namespace Orbital
{
	Scene::Scene(const SharedApplication& app) : SceneServices(app), mManager(new ECSManager(app))
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

	void Scene::deleteEntity(const EntityID& id)
	{
		if (mManager->entityExists(id))
			mManager->deleteEntity(id);
	}

	void Scene::requestDeleteEntity(const EntityID& id)
	{
		mManager->requestDeleteEntity(id);
	}

	void Scene::onLoad()
	{
		mManager->registerComponentType<TransformComponent>();
		mManager->registerComponentType<PhysicsComponent>();
		mManager->registerComponentType<MeshComponent>();
		mManager->registerComponentType<MeshFilter>();
		mManager->registerComponentType<NativeScriptManager>();

		preLoad();

		for (auto& [uuid, manager] : mManager->components<NativeScriptManager>())
		{
			manager.onLoad();
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

	void Scene::onStart()
	{
		for (auto& [uuid, manager] : mManager->components<NativeScriptManager>())
		{
			manager.onStart();
		}
	}

	void Scene::onPreUpdate(const Time& dt)
	{
		if (ScriptEngine.LastCompilationSucceeded())
		{
			for (auto& [uuid, manager] : mManager->components<NativeScriptManager>())
			{
				manager.onPreUpdate(dt);
			}
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

	void Scene::postUpdate()
	{
		mManager->deleteRequested();
	}
} // namespace Orbital
