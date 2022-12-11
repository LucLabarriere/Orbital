#include "OrbitalEngine/ECS/Components/PhysicsComponent.h"
#include "OrbitalPhysics/Colliders.h"

namespace Orbital
{
	template <>
	SafeHandle<PhysicsComponent> Entity::push<Orbital::PhysicsComponent, Orbital::ColliderType>(
		ColliderType colliderType
	)
	{
		assert(get<PhysicsComponent>().isValid() == false && "Entity already has the requested component");
		ECS::Registry* registry = mManager.lock()->getRegistry();

		auto transform = registry->get<TransformComponent>(mEntityID);
		auto physics = mManager.lock()->addPhysicsComponent(mEntityID, colliderType);

		if (transform.isValid())
		{
			// Setting the transform in the physics engine
			physics->setTransform(*transform);
			// Removing the transform from the ECS
			registry->remove<TransformComponent>(mEntityID);
		}

		return physics;
	}
} // namespace Orbital
