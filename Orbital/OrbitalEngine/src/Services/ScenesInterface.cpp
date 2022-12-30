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

	void ScenesInterface::Initialize()
	{
		mInstance = mApp.lock()->getSceneManager();
	}

	void ScenesInterface::OnLoad()
	{
		mInstance.lock()->onLoad();
	}

	void ScenesInterface::OnCleanUp()
	{
		mInstance.lock()->onCleanUp();
	}

	void ScenesInterface::OnStart()
	{
		mInstance.lock()->onStart();
	}

	void ScenesInterface::OnUpdate(const Time& dt)
	{
		mInstance.lock()->onUpdate(dt);
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
		mInstance.lock()->reload();
	}
} // namespace Orbital
