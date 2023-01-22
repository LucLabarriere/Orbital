#include "OrbitalPhysics/Calculations.h"

#include "OrbitalPhysics/Colliders.h"

namespace Orbital
{
	namespace Physics
	{
		namespace Calculations
		{
			auto GetPointPointCollisionData(PointCollider& p1, PointCollider& p2)
				-> CollisionData
			{
				return { .A = &p1, .B = &p2 };
			}

			auto GetPointSphereCollisionData(PointCollider& p, SphereCollider& s)
				-> CollisionData
			{
				const auto& transform_1 = p.getTransform();
				const auto& transform_2 = s.getTransform();
				float radius = transform_2.scale.x / 2.0f;
				auto difference = transform_2.position - transform_1.position;
				float distance = Maths::Magnitude(difference);
				bool collide = (distance < radius ? true : false);

				return { .A = &p, .B = &s, .collide = collide };
			}

			auto GetSphereSphereCollisionData(SphereCollider& s1, SphereCollider& s2)
				-> CollisionData
			{
				const auto& transform_1 = s1.getTransform();
				const auto& transform_2 = s2.getTransform();
				float radius_1 = transform_1.scale.x / 2.0f;
				float radius_2 = transform_2.scale.x / 2.0f;
				auto difference = transform_2.position - transform_1.position;
				float distance = Maths::Magnitude(difference);
				bool collide = (distance < radius_1 + radius_2 ? true : false);

				return { .A = &s1, .B = &s2, .collide = collide };
			}
		} // namespace Calculations
	}	  // namespace Physics
} // namespace Orbital
