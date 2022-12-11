#include "OrbitalEngine/ECS/Entity.h"
#include "OrbitalEngine/ECS/Components/PhysicsComponent.h"
#include "OrbitalEngine/ECS/Components/TransformComponent.h"
#include "OrbitalEngine/ECS/Components/NativeScriptManager.h"


namespace Orbital
{
	Entity::Entity(const EntityID& id, const std::weak_ptr<ECSManager>& manager) : mEntityID(id), mManager(manager)
	{
	}
	Entity::Entity(const Entity& other) : mEntityID(other.mEntityID), mManager(other.mManager)
	{
	}

	void Entity::pushNativeScript(const std::string& name)
	{
		auto manager = get<NativeScriptManager>();
		manager->push(name, *this);
	}

	void Entity::removePhysicsComponent()
	{
		// TODO Test
		auto physicsComponent = get<PhysicsComponent>();
		auto registry = mManager.lock()->getRegistry();
		//
		// Copying transform
		registry->push<TransformComponent>(mEntityID, physicsComponent->getTransform());
		registry->remove<PhysicsComponent>(mEntityID);
	}

	void Entity::removeTransformComponent()
	{
		auto physicsComponent = get<PhysicsComponent>();
		auto registry = mManager.lock()->getRegistry();

		// If physics component, raise an error because the transform cannot be removed
		assert(
			physicsComponent.isValid() == false &&
			"Trying to remove a transform from an object that has a PhysicsComponent"
		);

		registry->remove<TransformComponent>(mEntityID);
	}

	void Entity::destroy()
	{
		mManager.lock()->deleteEntity(mEntityID);
	}
} // namespace Orbital
