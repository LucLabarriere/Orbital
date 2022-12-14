#include "OrbitalPhysics/Colliders/SphereCollider.h"

namespace Orbital
{
	namespace Physics
	{
		SphereCollider::SphereCollider(const ColliderID& id) : Collider(id, SphereCollider::GetColliderType())
		{
		}

		SphereCollider::SphereCollider(const ColliderID& id, const Transform& transform)
			: Collider(id, SphereCollider::GetColliderType(), transform)
		{
		}

		CollisionData SphereCollider::checkCollision(Collider& other)
		{
			return other.checkCollision(*this);
		}

		CollisionData SphereCollider::checkCollision(PointCollider& other)
		{
			return Calculations::GetPointSphereCollisionData(other, *this);
		}

		CollisionData SphereCollider::checkCollision(SphereCollider& other)
		{
			return Calculations::GetSphereSphereCollisionData(other, *this);
		}
	} // namespace Physics
} // namespace Orbital
