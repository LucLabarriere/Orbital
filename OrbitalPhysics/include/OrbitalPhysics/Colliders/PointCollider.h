#pragma once

#include "OrbitalPhysics/Context.h"

#include "OrbitalPhysics/Colliders/Collider.h"
#include "OrbitalPhysics/Calculations.h"

namespace Orbital
{
	namespace Physics
	{
		class OPHYSICS_API PointCollider : public Collider
		{
		public:
			PointCollider(const ColliderType& type);
			PointCollider(const ColliderType& type, const Transform& transform);
			PointCollider(const PointCollider& other);

			static inline ColliderType GetColliderType()
			{
				return ColliderType::Point;
			}

			virtual CollisionData checkCollision(const Collider& other) const override;
			virtual CollisionData checkCollision(const PointCollider& other) const override;
			virtual CollisionData checkCollision(const SphereCollider& other) const override;
		};
	} // namespace Physics
} // namespace Orbital
