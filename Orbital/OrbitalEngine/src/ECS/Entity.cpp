#include "OrbitalEngine/ECS/Entity.h"
#include "OrbitalEngine/ECS/Components/NativeScriptManager.h"
#include "OrbitalEngine/ECS/Components/PhysicsComponent.h"
#include "OrbitalEngine/ECS/Components/TransformComponent.h"

namespace Orbital
{
	Entity::Entity(
		const SharedApplication& app, const EntityID& id,
		const WeakRef<ECSManager>& manager
	)
		: EntityServices(app), mEntityID(id), mManager(manager)
	{
		EntityServices::InitializeServices();
	}
	Entity::Entity(const SharedApplication& app, const Entity& other)
		: EntityServices(app), mEntityID(other.mEntityID), mManager(other.mManager)
	{
		EntityServices::InitializeServices();
	}

	void Entity::pushNativeScript(std::string_view name)
	{
		auto manager = get<NativeScriptManager>();
		manager->push(name, *this);
	}

	void Entity::removePhysicsComponent()
	{
		// TODO Test
		auto physicsComponent = get<PhysicsComponent>();
		auto registry = mManager.lock()->getRegistry();

		// Copying transform
		registry->push<TransformComponent>(mEntityID, physicsComponent->getTransform());
		registry->remove<PhysicsComponent>(mEntityID);
	}

	void Entity::removeTransformComponent()
	{
		auto physicsComponent = get<PhysicsComponent>();
		auto registry = mManager.lock()->getRegistry();

		// If physics component, raise an error because the transform cannot be removed
		Orbital::Assert(
			physicsComponent.isValid() == false,
			"Trying to remove a transform from an object that has a PhysicsComponent"
		);

		registry->remove<TransformComponent>(mEntityID);
	}

	void Entity::destroy()
	{
		mManager.lock()->deleteEntity(mEntityID);
	}
} // namespace Orbital
