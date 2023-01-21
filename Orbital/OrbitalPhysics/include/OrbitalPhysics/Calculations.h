#pragma once

#include "OrbitalPhysics/Context.h"

namespace Orbital
{
	namespace Physics 
	{
		struct CollisionData;
		class PointCollider;
		class SphereCollider;

		namespace Calculations
		{
			ORBITAL_PHYSICS_API CollisionData GetPointPointCollisionData(PointCollider& p1, PointCollider& p2);
			ORBITAL_PHYSICS_API CollisionData GetPointSphereCollisionData(PointCollider& p, SphereCollider& s);
			ORBITAL_PHYSICS_API CollisionData GetSphereSphereCollisionData(SphereCollider& p, SphereCollider& s);
		};
	} // namespace Orbital
} // namespace Orbital
