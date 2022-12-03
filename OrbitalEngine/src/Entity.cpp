#include "OrbitalEngine/Entity.h"
#include "OrbitalEngine/Components/PhysicsComponent.h"
#include "OrbitalEngine/Components/TransformComponent.h"

namespace Orbital
{
	ComponentHandle<TransformComponent> Entity::getTransform() const
	{
		auto physicsComponent = get<PhysicsComponent>();

		// If physics component, use the Physics Engine
		if (physicsComponent.isValid())
			return ComponentHandle<TransformComponent>(
				&physicsComponent->getTransform(), mBaseEntity.getID(), mBaseEntity.getRegistry()
			);

		// If no physics component, using the ECS instead
		return mBaseEntity.get<TransformComponent>();
	}

	void Entity::removePhysicsComponent()
	{
		// TODO Test
		auto physicsComponent = get<PhysicsComponent>();
		// Copying transform
		mBaseEntity.push<TransformComponent>(physicsComponent->getTransform());
		mBaseEntity.remove<PhysicsComponent>();
	}

	void Entity::removeTransformComponent()
	{
		auto physicsComponent = get<PhysicsComponent>();

		// If physics component, raise an error because the transform cannot be removed
		assert(
			physicsComponent.isValid() == false &&
			"Trying to remove a transform from an object that has a PhysicsComponent"
		);

		mBaseEntity.remove<TransformComponent>();
	}
} // namespace Orbital
