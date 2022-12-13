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
		mScene = mApp.lock()->getSceneManager().lock()->getCurrentScene();
		mManager = mScene.lock()->getManager();
	}

	void ECSInterface::Reset()
	{
		mManager.lock()->reset();
	}

	Entity ECSInterface::CreateEntity()
	{
		return mScene.lock()->createEntity();
	}

	void ECSInterface::DeleteEntity(const EntityID& id)
	{
		return mScene.lock()->deleteEntity(id);
	}

	Entity ECSInterface::GetEntity(const ECS::EntityID& entityID)
	{
		return mManager.lock()->getEntity(entityID);
	}
} // namespace Orbital
