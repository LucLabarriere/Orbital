#pragma once

#include "OrbitalPhysics/Context.h"

namespace Orbital
{
	namespace Physics
	{
		struct CollisionPoints
		{
			Maths::Vec3 A;
			Maths::Vec3 B;
			Maths::Vec3 Normal;
			float Depth;
			bool hasCollision;
		};
	} // namespace Physics
} // namespace Orbital
