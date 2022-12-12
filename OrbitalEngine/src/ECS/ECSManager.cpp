#include "OrbitalEngine/ECS/ECSManager.h"
#include "OrbitalEngine/ECS/Components/PhysicsComponent.h"
#include "OrbitalEngine/ECS/Entity.h"

#include "OrbitalPhysics/Colliders.h"
#include "OrbitalPhysics/Engine.h"

namespace Orbital
{
	Entity ECSManager::createEntity()
	{
		return Entity(mRegistry.createEntity().getID(), shared_from_this());
	}

	Entity ECSManager::getEntity(const EntityID& id)
	{
		return Entity(id, shared_from_this());
	}

	void ECSManager::deleteEntity(const EntityID& id)
	{
		mRegistry.deleteEntity(id);
	}
} // namespace Orbital
