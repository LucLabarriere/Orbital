#pragma once

#include "OrbitalPhysics/Context.h"

#include "OrbitalPhysics/Colliders/Collider.h"
#include "OrbitalPhysics/Calculations.h"

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

			static inline ColliderType GetColliderType()
			{
				return ColliderType::Sphere;
			}

			virtual Maths::Vec3 supportFunction(const Maths::Vec3& direction) const override
			{
				return direction * mTransform.scale.x / 2.0f;
			};
			
			virtual CollisionData checkCollision(Collider& other) override;
			virtual CollisionData checkCollision(PointCollider& other) override;
			virtual CollisionData checkCollision(SphereCollider& other) override;
		};
	} // namespace Physics
} // namespace Orbital
