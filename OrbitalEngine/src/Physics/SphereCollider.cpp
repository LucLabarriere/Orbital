#include "OrbitalEngine/Physics/SphereCollider.h"
#include "OrbitalEngine/Physics/PhysicsEngine.h"

namespace Orbital
{
	SphereCollider::SphereCollider(const TransformHandle& transform)
		: Collider(transform)
	{
		mType = "Sphere";
	}

	SphereCollider::SphereCollider(const TransformHandle& transform, const DynamicsHandle& dynamics)
		: Collider(transform, dynamics)
	{
		mType = "Sphere";
	}

	CollisionPoints SphereCollider::getCollisionPoints(const Collider& other) const
	{
		return other.getCollisionPoints(*this);
	}

	CollisionPoints SphereCollider::getCollisionPoints(const PlaneCollider& other) const
	{
		return PhysicsEngine::GetPlaneSphereCollisionPoints(other, *this);
	}

	CollisionPoints SphereCollider::getCollisionPoints(const SphereCollider& other) const
	{
		return PhysicsEngine::GetSphereSphereCollisionPoints(*this, other);
	}
} // namespace Orbital
