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

	auto ScenesInterface::GetCurrentScene() -> Unique<Scene>*
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

	auto ScenesInterface::GetState() -> SceneState
	{
		return mInstance.lock()->getState();
	}

	void ScenesInterface::SetMainCamera(const Entity& camera)
	{
		mInstance.lock()->setMainCamera(camera);
	}
} // namespace Orbital
