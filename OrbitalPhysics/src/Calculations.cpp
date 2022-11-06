#include "OrbitalPhysics/Calculations.h"

#include "OrbitalPhysics/Colliders.h"

namespace Orbital
{
	namespace Physics
	{
		CollisionData Calculations::GetPointPointCollisionData(const PointCollider& p1, const PointCollider& p2)
		{
			return {};
		}

		CollisionData Calculations::GetPointSphereCollisionData(const PointCollider& p, const SphereCollider& s)
		{
			auto difference = s.getPosition() - p.getPosition();
			float distance = Maths::Magnitude(difference);
			bool collide = (distance < s.getRadius() ? true : false);

			return { .collide = collide };
		}

		CollisionData Calculations::GetSphereSphereCollisionData(const SphereCollider& s1, const SphereCollider& s2)
		{
			auto difference = s1.getPosition() - s2.getPosition();
			float distance = Maths::Magnitude(difference);
			bool collide = (distance < s1.getRadius() + s2.getRadius() ? true : false);

			return { .collide = collide };
		}
	} // namespace Physics
} // namespace Orbital
