#include "OrbitalEngine/SceneManager.h"
#include "OrbitalEngine/OrbitalApplication.h"
#include "OrbitalScripts/FreeCameraController.h"

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
		pause();
	}

	void SceneManager::onCleanUp()
	{
		mScene->onCleanUp();
		pause();
	}

	void SceneManager::onStart()
	{
		mScene->onStart();
		resume();
	}

	void SceneManager::onPreUpdate(const Time& dt)
	{
		if (mState == SceneState::Running)
			mScene->onPreUpdate(dt);
		else
			mScene->getDevCamera().get<FreeCameraController>()->onPreUpdate(dt);
	}

	void SceneManager::onUpdate(const Time& dt)
	{
		if (mState == SceneState::Running)
			mScene->onUpdate(dt);
		else
			mScene->getDevCamera().get<FreeCameraController>()->onUpdate(dt);
	}

	void SceneManager::postUpdate()
	{
		if (mState == SceneState::Running)
			mScene->postUpdate();

		if (mRequestReload)
		{
			onCleanUp();
			mScene->initialize();
			onLoad();
			onStart();
			mRequestReload = false;
		}
	}

	void SceneManager::pause()
	{
		mState = SceneState::Paused;
		Renderer.SetCamera(mScene->getDevCamera().get<CameraComponent>());
	}

	void SceneManager::resume()
	{
		mState = SceneState::Running;
		Renderer.SetCamera(mScene->getMainCamera().get<CameraComponent>());
	}

	void SceneManager::reload()
	{
		mRequestReload = true;
	}
} // namespace Orbital
