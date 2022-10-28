#include "OrbitalEngine/Services/ECSService.h"
#include "OrbitalEngine/OrbitalApplication.h"
#include "OrbitalEngine/SceneManager.h"

namespace Orbital
{
	ECSInterface::ECSInterface(const SharedApplication& app)
		: ServiceInterface(app)
	{
	}

	void ECSInterface::Initialize()
	{
		mScene = mApp->getSceneManager()->getCurrentScene();
		mRegistry = (*mScene)->getRegistry();
	}

	void ECSInterface::Reset()
	{
		(*mRegistry)->reset();
	}

	Entity ECSInterface::CreateEntity()
	{
		return (*mScene)->createEntity();
	}

	Entity ECSInterface::GetEntity(const EntityID& entityID)
	{
		return (*mRegistry)->getEntity(entityID);
	}
} // namespace Orbital
