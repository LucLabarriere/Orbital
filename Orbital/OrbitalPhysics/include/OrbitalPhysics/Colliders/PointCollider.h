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
			PointCollider(const ColliderID& id);
			PointCollider(const ColliderID& id, const Transform& transform);

			PointCollider(const PointCollider& other) = delete;
			PointCollider(PointCollider&& other) = delete;

			virtual ~PointCollider(){};

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
