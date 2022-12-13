#include "OrbitalEngine/ECS/Components/PhysicsComponent.h"
#include "OrbitalPhysics/Colliders.h"

namespace Orbital
{
	template <>
	SafeHandle<PhysicsComponent> Entity::push<PhysicsComponent, Physics::ColliderType>(
		Physics::ColliderType colliderType
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
			registry->push<PhysicsComponent>(
				mEntityID, mEntityID, mManager, PhysicsEngine.Get(),
				PhysicsEngine.Get().lock()->push<Physics::PointCollider>(*transform)
			);
			break;
		}
		case Physics::ColliderType::Sphere:
		{
			registry->push<PhysicsComponent>(
				mEntityID, mEntityID, mManager, PhysicsEngine.Get(),
				PhysicsEngine.Get().lock()->push<Physics::SphereCollider>(*transform)
			);
			break;
		}
		}

		auto physics = SafeHandle<PhysicsComponent>(mEntityID, mManager);

		// Removing the TransformComponent since it is now handled by the PhysicsEngine
		registry->remove<TransformComponent>(mEntityID);

		return physics;
	}

	template <>
	SafeHandle<PhysicsComponent> Entity::push<PhysicsComponent>()
	{
		assert(false && "Not implemented");
	}
} // namespace Orbital
