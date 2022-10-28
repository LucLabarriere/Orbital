#include "OrbitalEngine/Services/ScenesService.h"
#include "OrbitalEngine/OrbitalApplication.h"
#include "OrbitalEngine/SceneManager.h"

namespace Orbital
{
	ScenesInterface::ScenesInterface(const SharedApplication& app) : ServiceInterface(app)
	{
	}

	void ScenesInterface::Initialize()
	{
		mInstance = mApp->getSceneManager();
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
