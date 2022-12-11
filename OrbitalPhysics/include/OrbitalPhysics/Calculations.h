#pragma once

#include "OrbitalPhysics/Context.h"

namespace Orbital
{
	namespace Physics 
	{
		class CollisionData;
		class PointCollider;
		class SphereCollider;

		namespace Calculations
		{
			OPHYSICS_API CollisionData GetPointPointCollisionData(const PointCollider& p1, const PointCollider& p2);
			OPHYSICS_API CollisionData GetPointSphereCollisionData(const PointCollider& p, const SphereCollider& s);
			OPHYSICS_API CollisionData GetSphereSphereCollisionData(const SphereCollider& p, const SphereCollider& s);
		};
	} // namespace Orbital
} // namespace Orbital
