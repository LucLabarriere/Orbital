#include "OrbitalPhysics/Colliders/SphereCollider.h"

namespace Orbital
{
	namespace Physics
	{
		SphereCollider::SphereCollider(const ColliderType& type) : Collider(type)
		{
		}

		SphereCollider::SphereCollider(const ColliderType& type, float radius) : Collider(type), mRadius(radius)
		{
		}

		SphereCollider::SphereCollider(const ColliderType& type, const Transform& transform) : Collider(type, transform), mRadius(1.0f)
		{
		}

		SphereCollider::SphereCollider(const ColliderType& type, const Transform& transform, float radius) : Collider(type, transform), mRadius(radius)
		{
		}

		SphereCollider::SphereCollider(const SphereCollider& other)
			: Collider(other.mType, other.mTransform), mRadius(other.mRadius)
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
