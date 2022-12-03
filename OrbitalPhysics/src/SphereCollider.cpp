#include "OrbitalPhysics/Colliders/SphereCollider.h"

namespace Orbital
{
	namespace Physics
	{
		SphereCollider::SphereCollider() : Collider()
		{
		}

		SphereCollider::SphereCollider(float radius) : Collider(), mRadius(radius)
		{
		}

		SphereCollider::SphereCollider(const Maths::Vec3& p, float radius) : Collider(p), mRadius(radius)
		{
		}

		SphereCollider::SphereCollider(const SphereCollider& other)
			: Collider(other.mTransform.position), mRadius(other.mRadius)
		{
		}

		CollisionData SphereCollider::checkCollision(const Collider& other) const
		{
			return other.checkCollision(*this);
		}

		CollisionData SphereCollider::checkCollision(const PointCollider& other) const
		{
			return Calculations::GetPointSphereCollisionData(other, *this);
		}

		CollisionData SphereCollider::checkCollision(const SphereCollider& other) const
		{
			return Calculations::GetSphereSphereCollisionData(other, *this);
		}
	} // namespace Physics
} // namespace Orbital
