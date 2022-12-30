#include "OrbitalEngine/SceneManager.h"
#include "OrbitalEngine/OrbitalApplication.h"

namespace Orbital
{
	SceneManager::SceneManager(const SharedApplication& app) : SceneManagerServices(app)
	{
		LOGFUNC();
	}

	void SceneManager::terminate()
	{
		mScene->terminate();
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
		if (mRunning)
			mScene->onPreUpdate(dt);
	}

	void SceneManager::onUpdate(const Time& dt)
	{
		if (mRunning)
			mScene->onUpdate(dt);
	}

	void SceneManager::postUpdate()
	{
		if (mRunning)
		{
			mScene->postUpdate();
		}

		if (mRequestReload)
		{
			mScene->onCleanUp();
			mScene->initialize();
			mScene->onLoad();
			mRequestReload = false;
		}
	}

	void SceneManager::pause()
	{
		mRunning = false;
	}

	void SceneManager::resume()
	{
		mRunning = true;
	}

	void SceneManager::reload()
	{
		mRequestReload = true;
	}

} // namespace Orbital
