#include "OrbitalPhysics/Colliders.h"
#include "OrbitalPhysics/Algorithms.h"

namespace Orbital
{

	Physics::CollisionPoints PlaneCollider::GetCollisionPoints(
		const Physics::Transform* transform, const PlaneCollider* collider, const Physics::Transform* otherTransform
	) const
	{
		return { };
	}

}
