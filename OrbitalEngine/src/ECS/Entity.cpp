#include "OrbitalEngine/ECS/Entity.h"
#include "OrbitalEngine/ECS/Components/PhysicsComponent.h"
#include "OrbitalEngine/ECS/Components/TransformComponent.h"

namespace Orbital
{
	Entity::Entity(const EntityID& id, ECSManager* manager) : mEntityID(id), mManager(manager)
	{
	}
	Entity::Entity(const Entity& other) : mEntityID(other.mEntityID), mManager(other.mManager)
		{
		}

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

	void Entity::destroy()
	{
		mManager->deleteEntity(mEntityID);
	}
} // namespace Orbital
