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
			OPHYSICS_API CollisionData GetPointPointCollisionData(PointCollider& p1, PointCollider& p2);
			OPHYSICS_API CollisionData GetPointSphereCollisionData(PointCollider& p, SphereCollider& s);
			OPHYSICS_API CollisionData GetSphereSphereCollisionData(SphereCollider& p, SphereCollider& s);
		};
	} // namespace Orbital
} // namespace Orbital
