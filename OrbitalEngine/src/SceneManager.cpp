#include "OrbitalEngine/SceneManager.h"
#include "OrbitalEngine/OrbitalApplication.h"

namespace Orbital
{
	SceneManager::SceneManager(const SharedApplication& app)
		: SceneManagerServices(app)
	{
		LOGFUNC();
	}

	void SceneManager::initialize()
	{
		LOGFUNC();
		mScene = new Scene(mApp);
	}

	void SceneManager::terminate()
	{
		LOGFUNC();
		mScene->terminate();
		Logger::Debug("Deleting scene");
		delete mScene;
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

	void SceneManager::onUpdate(const Time& dt)
	{
		mScene->onUpdate(dt);
	}
} // namespace Orbital
