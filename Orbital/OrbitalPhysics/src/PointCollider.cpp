#include "OrbitalPhysics/Colliders/PointCollider.h"

namespace Orbital
{
	namespace Physics
	{
		PointCollider::PointCollider(const ColliderID& id) : Collider(id, PointCollider::GetColliderType())
		{
		}

		PointCollider::PointCollider(const ColliderID& id, const Transform& transform)
			: Collider(id, PointCollider::GetColliderType(), transform)
		{
		}

		CollisionData PointCollider::checkCollision(Collider& other)
		{
			return other.checkCollision(*this);
		}

		CollisionData PointCollider::checkCollision(PointCollider& other)
		{
			return Calculations::GetPointPointCollisionData(other, *this);
		}

		CollisionData PointCollider::checkCollision(SphereCollider& other)
		{
			return Calculations::GetPointSphereCollisionData(*this, other);
		}
	} // namespace Physics
} // namespace Orbital
