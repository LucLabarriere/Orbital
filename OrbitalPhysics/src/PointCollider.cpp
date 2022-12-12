#include "OrbitalPhysics/Colliders/PointCollider.h"

namespace Orbital
{
	namespace Physics
	{
		PointCollider::PointCollider(const ColliderType& type) : Collider(type)
		{
		}

		PointCollider::PointCollider(const ColliderType& type, const Transform& transform) : Collider(type, transform)
		{
		}

		PointCollider::PointCollider(const PointCollider& other) : Collider(other.mType, other.mTransform)
		{
		}

		CollisionData PointCollider::checkCollision(const Collider& other) const
		{
			return other.checkCollision(*this);
		}

		CollisionData PointCollider::checkCollision(const PointCollider& other) const
		{
			return Calculations::GetPointPointCollisionData(other, *this);
		}

		CollisionData PointCollider::checkCollision(const SphereCollider& other) const
		{
			return Calculations::GetPointSphereCollisionData(*this, other);
		}
	} // namespace Physics
} // namespace Orbital
