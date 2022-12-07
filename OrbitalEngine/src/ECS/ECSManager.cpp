#include "OrbitalEngine/ECS/ECSManager.h"
#include "OrbitalEngine/ECS/Entity.h"

namespace Orbital
{
	Entity ECSManager::createEntity()
	{
		return Entity(mRegistry.createEntity().getID(), this);
	}

	Entity ECSManager::getEntity(const EntityID& id)
	{
		return Entity(id, this);
	}

	void ECSManager::deleteEntity(const EntityID& id)
	{
		mRegistry.deleteEntity(id);
	}
}
