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
} // namespace Orbital
