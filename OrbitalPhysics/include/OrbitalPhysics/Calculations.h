#pragma once

#include "OrbitalPhysics/Context.h"

namespace Orbital
{
	namespace Physics 
	{
		class CollisionData;
		class PointCollider;
		class SphereCollider;

		class OPHYSICS_API Calculations
		{
		public:
			static CollisionData GetPointPointCollisionData(const PointCollider& p1, const PointCollider& p2);
			static CollisionData GetPointSphereCollisionData(const PointCollider& p, const SphereCollider& s);
			static CollisionData GetSphereSphereCollisionData(const SphereCollider& p, const SphereCollider& s);
		};
	} // namespace Orbital
} // namespace Orbital
