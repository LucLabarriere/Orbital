#pragma once

#include "OrbitalPhysics/Context.h"

#include "OrbitalPhysics/Calculations.h"
#include "OrbitalPhysics/Colliders/Collider.h"

namespace Orbital
{
	namespace Physics
	{
		class ORBITAL_PHYSICS_API PointCollider : public Collider
		{
		public:
			PointCollider(const ColliderID& id);
			PointCollider(const ColliderID& id, const Transform& transform);

			PointCollider(const PointCollider& other) = delete;
			PointCollider(PointCollider&& other) = delete;

			virtual ~PointCollider(){};

			static inline auto GetColliderType() -> ColliderType
			{
				return ColliderType::Point;
			}

			virtual auto checkCollision(Collider& other) -> CollisionData override;
			virtual auto checkCollision(PointCollider& other) -> CollisionData override;
			virtual auto checkCollision(SphereCollider& other) -> CollisionData override;
		};
	} // namespace Physics
} // namespace Orbital
