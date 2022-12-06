#include "OrbitalEngine/ECS/Entity.h"
#include "OrbitalEngine/Components/PhysicsComponent.h"
#include "OrbitalEngine/Components/TransformComponent.h"

namespace Orbital
{
	void Entity::removePhysicsComponent()
	{
		// TODO Test
		auto physicsComponent = get<PhysicsComponent>();
		auto registry = mManager->getRegistry();
		//
		// Copying transform
		registry->push<TransformComponent>(mEntityID, physicsComponent->getTransform());
		registry->remove<PhysicsComponent>(mEntityID);
	}

	void Entity::removeTransformComponent()
	{
		auto physicsComponent = get<PhysicsComponent>();
		auto registry = mManager->getRegistry();

		// If physics component, raise an error because the transform cannot be removed
		assert(
			physicsComponent.isValid() == false &&
			"Trying to remove a transform from an object that has a PhysicsComponent"
		);

		registry->remove<TransformComponent>(mEntityID);
	}
} // namespace Orbital
