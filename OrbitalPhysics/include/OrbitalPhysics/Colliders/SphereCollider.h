#pragma once

#include "OrbitalPhysics/Context.h"

#include "OrbitalPhysics/Colliders/Collider.h"
#include "OrbitalPhysics/Calculations.h"

namespace Orbital
{
	namespace Physics
	{
		class OPHYSICS_API SphereCollider : public Collider
		{
		public:
			SphereCollider(const ColliderType& type);
			SphereCollider(const ColliderType& type, float radius);
			SphereCollider(const ColliderType& type, const Transform& transform);
			SphereCollider(const ColliderType& type, const Transform& transform, float radius);
			SphereCollider(const SphereCollider& other);

			static inline ColliderType GetColliderType()
			{
				return ColliderType::Sphere;
			}

			virtual Maths::Vec3 supportFunction(const Maths::Vec3& direction) const override
			{
				return direction * mRadius;
			};
			
			virtual CollisionData checkCollision(Collider& other) override;
			virtual CollisionData checkCollision(PointCollider& other) override;
			virtual CollisionData checkCollision(SphereCollider& other) override;

			inline void setRadius(float value) { mRadius = value; }
			float getRadius() const { return mRadius; }

		private:
			float mRadius = 1.0f;
		};
	} // namespace Physics
} // namespace Orbital
