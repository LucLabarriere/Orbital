#pragma once

#include "OrbitalPhysics/Context.h"

#include "OrbitalPhysics/Calculations.h"
#include "OrbitalPhysics/Colliders/Collider.h"

namespace Orbital
{
	namespace Physics
	{
		class ORBITAL_PHYSICS_API SphereCollider : public Collider
		{
		public:
			SphereCollider(const ColliderID& id);
			SphereCollider(const ColliderID& id, const Transform& transform);

			SphereCollider(const SphereCollider& other) = delete;
			SphereCollider(SphereCollider&& other) = delete;

			virtual ~SphereCollider(){};

			static inline auto GetColliderType() -> ColliderType
			{
				return ColliderType::Sphere;
			}

			virtual auto supportFunction(const Maths::Vec3& direction) const
				-> Maths::Vec3 override
			{
				return direction * mTransform.scale.x / 2.0f;
			};

			virtual auto checkCollision(Collider& other) -> CollisionData override;
			virtual auto checkCollision(PointCollider& other) -> CollisionData override;
			virtual auto checkCollision(SphereCollider& other) -> CollisionData override;
		};
	} // namespace Physics
} // namespace Orbital
