#include "OrbitalPhysics/Calculations.h"

#include "OrbitalPhysics/Colliders.h"

namespace Orbital
{
	namespace Physics
	{
		namespace Calculations
		{
		CollisionData GetPointPointCollisionData(const PointCollider& p1, const PointCollider& p2)
		{
			return {};
		}

		CollisionData GetPointSphereCollisionData(const PointCollider& p, const SphereCollider& s)
		{
			const auto& transform_1 = p.getTransform();
			const auto& transform_2 = s.getTransform();
			auto difference = transform_2.position - transform_1.position;
			float distance = Maths::Magnitude(difference);
			bool collide = (distance < s.getRadius() ? true : false);

			return { .collide = collide };
		}

		CollisionData GetSphereSphereCollisionData(const SphereCollider& s1, const SphereCollider& s2)
		{
			const auto& transform_1 = s1.getTransform();
			const auto& transform_2 = s2.getTransform();
			auto difference = transform_2.position - transform_1.position;
			float distance = Maths::Magnitude(difference);
			bool collide = (distance < s1.getRadius() + s2.getRadius() ? true : false);

			return { .collide = collide };
		}
		}
	} // namespace Physics
} // namespace Orbital
