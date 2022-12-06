#include "OrbitalEngine/Components/PhysicsComponent.h"
#include "OrbitalPhysics/Colliders.h"

namespace Orbital
{
	PhysicsComponent PhysicsComponent::Create(Physics::Engine& engine, const ColliderType& colliderType)
	{

		switch (colliderType)
		{
		case ColliderType::POINT_COLLIDER:
		{
			std::shared_ptr<Physics::Collider> collider = nullptr;
			return PhysicsComponent(collider);
		}
		case ColliderType::SPHERE_COLLIDER:
		{
			auto collider = std::make_shared<Physics::SphereCollider>();
			return PhysicsComponent(static_pointer_cast<Physics::Collider>(collider));
		}
		}
	}

	// SafeHandle IMPLEMENTATIONS
	template <>
	const TransformComponent& SafeHandle<TransformComponent>::operator*() const
	{
		const ECS::Registry* registry = mManager->getRegistry();
			ECS::Handle<PhysicsComponent> physics = registry->get<PhysicsComponent>(mEntityID);

			if (physics.isValid())
			{
				return physics->getTransform();
			}

			ECS::Handle<TransformComponent> transform = registry->get<TransformComponent>(mEntityID);

			assert(transform.isValid() && "The object has no TransformComponent nor PhysicsComponent");
			return *transform;
	}

	template <>
	TransformComponent& SafeHandle<TransformComponent>::operator*()
	{
		return OE_UNCONST(TransformComponent&, SafeHandle<TransformComponent>, operator*);
	}

	template <>
	bool SafeHandle<TransformComponent>::isValid() const
	{
		const ECS::Registry* registry = mManager->getRegistry();
		
		ECS::Handle<PhysicsComponent> physics = registry->get<PhysicsComponent>(mEntityID);

		if (physics.isValid())
		{
			return true; 
		}

		ECS::Handle<TransformComponent> transform = registry->get<TransformComponent>(mEntityID);

		return transform.isValid();
	}
} // namespace Orbital
