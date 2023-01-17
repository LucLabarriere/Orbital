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
		for (auto& [uuid, manager] : mManager->components<NativeScriptManager>())
		{
			manager.onCleanUp();
		}

		for (auto& [uuid, manager] : mDevManager->components<NativeScriptManager>())
		{
			manager.onCleanUp();
		}

		mManager->cleanUp();
		mDevManager->cleanUp();

		mManager.reset();
		mDevManager.reset();
	}

	void Scene::initialize()
	{
		registerDefaultComponents(mManager);
		registerDefaultComponents(mDevManager);
		registerCustomComponents();

		mDevCamera = mDevManager->createEntity();
		mDevCamera.push<NativeScriptManager>(mApp);
		mDevCamera.push<CameraComponent>(CameraSpecs{
			.behavior = CameraBehavior::Type::Free,
			.projection = CameraProjection::Type::Perspective,
		});
		mDevCamera.push<FreeCameraController>();
	}

	void Scene::load()
	{
		// Duplicate code, create a LayerStack to handle all layers instead
		preLoad(); // Loads the core script

		for (auto& [uuid, manager] : mManager->components<NativeScriptManager>())
		{
			manager.onLoad();
		}

		for (auto& [uuid, manager] : mDevManager->components<NativeScriptManager>())
		{
			manager.onLoad();
		}

		mState = SceneState::Stoped;
	}

	void Scene::start()
	{
		for (auto& [uuid, manager] : mManager->components<NativeScriptManager>())
		{
			manager.onStart();
		}
	}

	void Scene::pause()
	{
		mState = SceneState::Paused;
	}

	void Scene::resume()
	{
		mState = SceneState::Running;
	}

	void Scene::stop()
	{
		mManager->reset();
		mState = SceneState::Stoped;
		load();
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

	void Scene::preUpdate(const Time& dt)
	{
		if (ScriptEngine.LastCompilationSucceeded())
		{
			if (mState == SceneState::Running)
			{
				for (auto& [uuid, manager] : mManager->components<NativeScriptManager>())
				{
					manager.onPreUpdate(dt);
				}
			}
			else
			{
				for (auto& [uuid, manager] : mDevManager->components<NativeScriptManager>())
				{
					manager.onPreUpdate(dt);
				}
			}
		}
	}

	void Scene::update(const Time& dt)
	{
		if (ScriptEngine.LastCompilationSucceeded())
		{
			if (mState == SceneState::Running)
			{
				for (auto& [uuid, manager] : mManager->components<NativeScriptManager>())
				{
					manager.onUpdate(dt);
				}
			}
			else
			{
				for (auto& [uuid, manager] : mDevManager->components<NativeScriptManager>())
				{
					manager.onUpdate(dt);
				}
			}
		}
	}

	void Scene::postUpdate(const Time& dt)
	{
		if (ScriptEngine.LastCompilationSucceeded())
		{
			if (mState == SceneState::Running)
			{
				for (auto& [uuid, manager] : mManager->components<NativeScriptManager>())
				{
					manager.onPostUpdate(dt);
				}
			}
			else
			{
				for (auto& [uuid, manager] : mDevManager->components<NativeScriptManager>())
				{
					manager.onPostUpdate(dt);
				}
			}
		}
		mManager->deleteRequested();
	}

	void Scene::registerDefaultComponents(Ref<ECSManager>& manager)
	{
		manager->registerComponentType<TransformComponent>();
		manager->registerComponentType<PhysicsComponent>();
		manager->registerComponentType<MeshComponent>();
		manager->registerComponentType<MeshFilter>();
		manager->registerComponentType<NativeScriptManager>();
		manager->registerComponentType<CameraComponent>();
	}
} // namespace Orbital
