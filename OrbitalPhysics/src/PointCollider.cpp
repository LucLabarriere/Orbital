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
