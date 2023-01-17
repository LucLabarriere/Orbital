#include "OrbitalEngine/Services/ScenesInterface.h"
#include "OrbitalEngine/OrbitalApplication.h"
#include "OrbitalEngine/SceneManager.h"

namespace Orbital
{
	ScenesInterface::ScenesInterface() : ServiceInterface()
	{
	}

	ScenesInterface::ScenesInterface(const SharedApplication& app) : ServiceInterface(app)
	{
	}

	void ScenesInterface::InitializeInterface()
	{
		mInstance = mApp.lock()->getSceneManager();
	}

	Unique<Scene>* ScenesInterface::GetCurrentScene()
	{
		return mInstance.lock()->getCurrentScene();
	}

	void ScenesInterface::Pause()
	{
		mInstance.lock()->pause();
	}

	void ScenesInterface::Resume()
	{
		mInstance.lock()->resume();
	}

	void ScenesInterface::Reload()
	{
		mInstance.lock()->stop();
	}

	SceneState ScenesInterface::GetState()
	{
		return mInstance.lock()->getState();
	}

	void ScenesInterface::SetMainCamera(const Entity& camera)
	{
		mInstance.lock()->setMainCamera(camera);
	}
} // namespace Orbital
