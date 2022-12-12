#include "OrbitalEngine/ECS/Components/PhysicsComponent.h"
#include "OrbitalPhysics/Colliders.h"

namespace Orbital
{
	template <>
	SafeHandle<PhysicsComponent> Entity::push<PhysicsComponent, std::weak_ptr<Physics::Engine>, Physics::ColliderType>(
		std::weak_ptr<Physics::Engine> engine, Physics::ColliderType colliderType
	)
	{
		assert(get<PhysicsComponent>().isValid() == false && "Entity already has the requested component");
		ECS::Registry* registry = mManager.lock()->getRegistry();

		auto transform = registry->get<TransformComponent>(mEntityID);

		if (!transform.isValid())
		{
			transform = registry->push<TransformComponent>(mEntityID);
		}

		switch (colliderType)
		{
		case Physics::ColliderType::Point:
		{
			registry->push<PhysicsComponent>(mEntityID, engine, engine.lock()->push<Physics::PointCollider>(*transform));
			break;
		}
		case Physics::ColliderType::Sphere:
		{
			registry->push<PhysicsComponent>(mEntityID, engine, engine.lock()->push<Physics::SphereCollider>(*transform));
			break;
		}
		}

		auto physics = SafeHandle<PhysicsComponent>(mEntityID, mManager);
		// Removing the TransformComponent since it is now handled by the PhysicsEngine
		registry->remove<TransformComponent>(mEntityID);

		return physics;
	}

	template <>
	SafeHandle<PhysicsComponent> Entity::push<PhysicsComponent, std::weak_ptr<Physics::Engine>>(
		std::weak_ptr<Physics::Engine> engine
	)
	{
		assert(false && "Not implemented");
	}
} // namespace Orbital
