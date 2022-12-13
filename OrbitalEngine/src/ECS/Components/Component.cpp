#include "OrbitalEngine/ECS/Components/Component.h"
#include "OrbitalEngine/ECS/Entity.h"

namespace Orbital
{
	Component::Component(const EntityID& entityID, const WeakRef<ECSManager>& manager)
		: mEntityID(entityID), mManager(manager)
	{

	}

	Entity Component::getEntity() const
	{
		return Entity(mEntityID, mManager);
	}
}
