#include "OrbitalEngine/ECS/Components/PhysicsComponent.h"
#include "OrbitalPhysics/Colliders.h"

namespace Orbital
{
	PhysicsComponent::PhysicsComponent(
		const Component::InitArgs& c, const WeakRef<Physics::Engine>& engine
	)
		: Component(c), mEngine(engine)
	{
	}

	template <>
	auto Entity::push<PhysicsComponent, Physics::ColliderType>(
		Physics::ColliderType&& colliderType
	) -> SafeHandle<PhysicsComponent>
	{
		Orbital::Assert(
			!get<PhysicsComponent>().isValid(),
			"Entity already has the requested component"
		);
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
			PhysicsEngine.Get().lock()->pushAt<Physics::PointCollider>(
				mEntityID, *transform
			);
			registry->push<PhysicsComponent>(
				mEntityID, getComponentArgs(), PhysicsEngine.Get()
			);
			break;
		}
		case Physics::ColliderType::Sphere:
		{
			PhysicsEngine.Get().lock()->pushAt<Physics::SphereCollider>(
				mEntityID, *transform
			);
			registry->push<PhysicsComponent>(
				mEntityID, getComponentArgs(), PhysicsEngine.Get()
			);
			break;
		}
		}

		auto physics = SafeHandle<PhysicsComponent>(mEntityID, mManager);

		// Removing the TransformComponent since it is now handled by the
		// PhysicsEngine
		registry->remove<TransformComponent>(mEntityID);

		return physics;
	}

	template <>
	auto Entity::push<PhysicsComponent>() -> SafeHandle<PhysicsComponent>
	{
		Orbital::Assert(false,
						"Not implemented"); // TODO replace by an exception
		return push<PhysicsComponent>(Physics::ColliderType::Sphere);
	}
} // namespace Orbital
