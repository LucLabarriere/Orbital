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
			ORBITAL_PHYSICS_API auto GetPointPointCollisionData(
				PointCollider& p1, PointCollider& p2
			) -> CollisionData;
			ORBITAL_PHYSICS_API auto GetPointSphereCollisionData(
				PointCollider& p, SphereCollider& s
			) -> CollisionData;
			ORBITAL_PHYSICS_API auto GetSphereSphereCollisionData(
				SphereCollider& p, SphereCollider& s
			) -> CollisionData;
		}; // namespace Calculations
	}	   // namespace Physics
} // namespace Orbital
