#include "OrbitalEngine/ECS/Components/Component.h"
#include "OrbitalEngine/ECS/Entity.h"

namespace Orbital
{
	Component::Component(const Component::InitArgs& args)
		: mEntityID(args.entityID), mManager(std::move(args.manager))
	{
	}

	Entity Component::getEntity() const
	{
		return mManager.lock()->getEntity(mEntityID);
	}
}
