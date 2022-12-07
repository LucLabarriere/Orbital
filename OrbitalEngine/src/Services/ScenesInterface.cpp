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
		mInstance->onLoad();
	}

	void ScenesInterface::OnCleanUp()
	{
		mInstance->onCleanUp();
	}

	void ScenesInterface::OnStart()
	{
		mInstance->onStart();
	}

	void ScenesInterface::OnUpdate(const Time& dt)
	{
		mInstance->onUpdate(dt);
	}
} // namespace Orbital
