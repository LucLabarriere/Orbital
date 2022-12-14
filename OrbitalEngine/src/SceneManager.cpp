#include "OrbitalEngine/SceneManager.h"
#include "OrbitalEngine/OrbitalApplication.h"

namespace Orbital
{
	SceneManager::SceneManager(const SharedApplication& app)
		: SceneManagerServices(app)
	{
	}

	void SceneManager::initialize()
	{
		mScene = MakeRef<Scene>(mApp);
	}

	void SceneManager::terminate()
	{
		LOGFUNC();
		mScene->terminate();
		Logger::Debug("Deleting scene");
		mScene.reset();
	}

	void SceneManager::onLoad()
	{
		mScene->onLoad();
	}

	void SceneManager::onCleanUp()
	{
		mScene->onCleanUp();
	}

	void SceneManager::onStart()
	{
		mScene->onStart();
	}

	void SceneManager::onPreUpdate(const Time& dt)
	{
		mScene->onPreUpdate(dt);
	}

	void SceneManager::onUpdate(const Time& dt)
	{
		mScene->onUpdate(dt);
	}

	void SceneManager::postUpdate()
	{
		mScene->postUpdate();
	}
} // namespace Orbital
