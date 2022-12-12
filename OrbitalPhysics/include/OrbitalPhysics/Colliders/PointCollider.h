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

			virtual CollisionData checkCollision(Collider& other) override;
			virtual CollisionData checkCollision(PointCollider& other) override;
			virtual CollisionData checkCollision(SphereCollider& other) override;
		};
	} // namespace Physics
} // namespace Orbital
