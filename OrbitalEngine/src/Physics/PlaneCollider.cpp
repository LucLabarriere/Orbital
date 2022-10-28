#include "OrbitalEngine/Physics/PlaneCollider.h"
#include "OrbitalEngine/Physics/PhysicsEngine.h"

namespace Orbital
{
	PlaneCollider::PlaneCollider(const TransformHandle& transform)
		: Collider(transform)
	{
		mType = "Plane";
	}

	PlaneCollider::PlaneCollider(const TransformHandle& transform, const DynamicsHandle& dynamics)
		: Collider(transform, dynamics)
	{
		mType = "Plane";
	}

	CollisionPoints PlaneCollider::getCollisionPoints(const Collider& other) const
	{
		return other.getCollisionPoints(*this);
	}

	CollisionPoints PlaneCollider::getCollisionPoints(const PlaneCollider& other) const
	{
		return PhysicsEngine::GetPlanePlaneCollisionPoints(*this, other);
	}

	CollisionPoints PlaneCollider::getCollisionPoints(const SphereCollider& other) const
	{
		return PhysicsEngine::GetPlaneSphereCollisionPoints(*this, other);
	}
} // namespace Orbital
