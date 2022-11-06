#include "OrbitalPhysics/Colliders/PointCollider.h"

namespace Orbital
{
	namespace Physics
	{
		PointCollider::PointCollider() : Collider()
		{
		}

		PointCollider::PointCollider(const Maths::Vec3& p) : Collider(p)
		{
		}

		PointCollider::PointCollider(const PointCollider& other) : Collider(other.mPosition)
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
