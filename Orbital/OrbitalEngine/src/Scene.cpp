#include "OrbitalEngine/Scene.h"
#include "OrbitalEngine/ECS/Components/NativeScriptManager.h"
#include "OrbitalEngine/ScriptsLibraryLoader.h"

#include "OrbitalEngine/ECS/Components.h"
#include "OrbitalScripts/FreeCameraController.h"

namespace Orbital
{
	Scene::Scene(const SharedApplication& app)
		: SceneServices(app), mManager(new ECSManager(app)), mDevManager(new ECSManager(app))
	{
		SceneServices::InitializeServices();
	}

	void Scene::terminate()
	{
		LOGFUNC();
		mManager->cleanUp();
		mDevManager->cleanUp();

		mManager.reset();
		mDevManager.reset();
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
		mManager->registerComponentType<CameraComponent>();

		mDevManager->registerComponentType<TransformComponent>();
		mDevManager->registerComponentType<PhysicsComponent>();
		mDevManager->registerComponentType<MeshComponent>();
		mDevManager->registerComponentType<MeshFilter>();
		mDevManager->registerComponentType<NativeScriptManager>();
		mDevManager->registerComponentType<CameraComponent>();

		preLoad();

		// TODO
		// Have 2 modes : ORBITAL_DEV and ORBITAL_GAME
		// Don't do that in ORBITAL_GAME mode

		mDevCamera = mDevManager->createEntity();
		mDevCamera.push<NativeScriptManager>(mApp)->onLoad();
		mDevCamera.push<CameraComponent>(CameraSpecs{
			.behavior = CameraBehavior::Type::Free,
			.projection = CameraProjection::Type::Perspective,
		});
		mDevCamera.push<FreeCameraController>();

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

		for (auto& [uuid, manager] : mDevManager->components<NativeScriptManager>())
		{
			manager.onCleanUp();
		}

		mManager->reset();
		mDevManager->reset();
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
