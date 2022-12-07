#include "OrbitalEngine/Services/ECSInterface.h"
#include "OrbitalEngine/OrbitalApplication.h"
#include "OrbitalEngine/SceneManager.h"

namespace Orbital
{
	ECSInterface::ECSInterface()
		: ServiceInterface()
	{
	}
	ECSInterface::ECSInterface(const SharedApplication& app)
		: ServiceInterface(app)
	{
	}

	void ECSInterface::Initialize()
	{
		mScene = mApp.lock()->getSceneManager()->getCurrentScene();
		mManager = (*mScene)->getManager();
	}

	void ECSInterface::Reset()
	{
		(*mManager)->reset();
	}

	Entity ECSInterface::CreateEntity()
	{
		return (*mScene)->createEntity();
	}

	Entity ECSInterface::GetEntity(const ECS::EntityID& entityID)
	{
		return (*mManager)->getEntity(entityID);
	}
} // namespace Orbital
