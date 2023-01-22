#include "OrbitalPhysics/Colliders/SphereCollider.h"

namespace Orbital
{
	namespace Physics
	{
		SphereCollider::SphereCollider(const ColliderID& id)
			: Collider(id, SphereCollider::GetColliderType())
		{
		}

		SphereCollider::SphereCollider(const ColliderID& id, const Transform& transform)
			: Collider(id, SphereCollider::GetColliderType(), transform)
		{
		}

		auto SphereCollider::checkCollision(Collider& other) -> CollisionData
		{
			return other.checkCollision(*this);
		}

		auto SphereCollider::checkCollision(PointCollider& other) -> CollisionData
		{
			return Calculations::GetPointSphereCollisionData(other, *this);
		}

		auto SphereCollider::checkCollision(SphereCollider& other) -> CollisionData
		{
			return Calculations::GetSphereSphereCollisionData(other, *this);
		}
	} // namespace Physics
} // namespace Orbital
