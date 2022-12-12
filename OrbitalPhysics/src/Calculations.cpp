#include "OrbitalPhysics/Calculations.h"

#include "OrbitalPhysics/Colliders.h"

namespace Orbital
{
	namespace Physics
	{
		namespace Calculations
		{
			CollisionData GetPointPointCollisionData(PointCollider& p1, PointCollider& p2)
			{
				return {};
			}

			CollisionData GetPointSphereCollisionData(PointCollider& p, SphereCollider& s)
			{
				const auto& transform_1 = p.getTransform();
				const auto& transform_2 = s.getTransform();
				auto difference = transform_2.position - transform_1.position;
				float distance = Maths::Magnitude(difference);
				bool collide = (distance < s.getRadius() ? true : false);

				return { .A = &p, .B = &s, .collide = collide};
			}

			CollisionData GetSphereSphereCollisionData(SphereCollider& s1, SphereCollider& s2)
			{
				const auto& transform_1 = s1.getTransform();
				const auto& transform_2 = s2.getTransform();
				auto difference = transform_2.position - transform_1.position;
				float distance = Maths::Magnitude(difference);
				bool collide = (distance < s1.getRadius() + s2.getRadius() ? true : false);

				return { .A = &s1, .B = &s2, .collide = collide};
			}
		} // namespace Calculations
	}	  // namespace Physics
} // namespace Orbital
