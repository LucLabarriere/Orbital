#include "OrbitalPhysics/Colliders/PointCollider.h"

namespace Orbital
{
	namespace Physics
	{
		PointCollider::PointCollider(const ColliderID& id)
			: Collider(id, PointCollider::GetColliderType())
		{
		}

		PointCollider::PointCollider(const ColliderID& id, const Transform& transform)
			: Collider(id, PointCollider::GetColliderType(), transform)
		{
		}

		auto PointCollider::checkCollision(Collider& other) -> CollisionData
		{
			return other.checkCollision(*this);
		}

		auto PointCollider::checkCollision(PointCollider& other) -> CollisionData
		{
			return Calculations::GetPointPointCollisionData(other, *this);
		}

		auto PointCollider::checkCollision(SphereCollider& other) -> CollisionData
		{
			return Calculations::GetPointSphereCollisionData(*this, other);
		}
	} // namespace Physics
} // namespace Orbital
