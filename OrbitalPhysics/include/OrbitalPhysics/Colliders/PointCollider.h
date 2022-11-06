#pragma once

#include "OrbitalPhysics/Context.h"

#include "OrbitalPhysics/Colliders/Collider.h"
#include "OrbitalPhysics/Calculations.h"

namespace Orbital
{
	namespace Physics
	{
		class PointCollider : public Collider
		{
		public:
			PointCollider();
			PointCollider(const Maths::Vec3& p);
			PointCollider(const PointCollider& other);

			virtual CollisionData checkCollision(const Collider& other) const override;
			virtual CollisionData checkCollision(const PointCollider& other) const override;
			virtual CollisionData checkCollision(const SphereCollider& other) const override;
		};
	} // namespace Physics
} // namespace Orbital
