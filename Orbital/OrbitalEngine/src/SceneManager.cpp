#include "OrbitalEngine/SceneManager.h"
#include "OrbitalEngine/Scene.h"

namespace Orbital
{
	SceneManager::SceneManager(const SharedApplication& app)
		: SceneManagerServices(app), mScene(nullptr)
	{
	}

	void SceneManager::terminate()
	{
		mScene->terminate();
		mScene.reset();
	}

	void SceneManager::start()
	{
		mScene->start();
	}

	void SceneManager::pause()
	{
		mScene->pause();
	}

	void SceneManager::resume()
	{
		mScene->resume();
	}

	void SceneManager::stop()
	{
		mRequestReload = true;
	}

	void SceneManager::preUpdate(const Time& dt)
	{
		mScene->preUpdate(dt);
	}

	void SceneManager::update(const Time& dt)
	{
		mScene->update(dt);
	}

	void SceneManager::postUpdate(const Time& dt)
	{
		mScene->postUpdate(dt);

		if (mRequestReload)
		{
			mScene->stop();
			mRequestReload = false;
		}
	}

	void SceneManager::setScene(Unique<Scene>&& scene)
	{
		mScene = std::move(scene);
		mScene->initialize();
		mScene->load();
		mScene->start();
	}

	void SceneManager::setMainCamera(const Entity& camera)
	{
		mScene->setMainCamera(camera);
	}

	auto SceneManager::getCurrentScene() -> Unique<Scene>*
	{
		return &mScene;
	}
	auto SceneManager::getState() const -> SceneState
	{
		return mScene->getState();
	}

} // namespace Orbital
