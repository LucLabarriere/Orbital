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
			SphereCollider();
			SphereCollider(float radius);
			SphereCollider(const Maths::Vec3& p, float radius);
			SphereCollider(const SphereCollider& other);

			virtual Maths::Vec3 supportFunction(const Maths::Vec3& direction) const override
			{
				return direction * mRadius;
			};
			
			virtual CollisionData checkCollision(const Collider& other) const override;
			virtual CollisionData checkCollision(const PointCollider& other) const override;
			virtual CollisionData checkCollision(const SphereCollider& other) const override;

			float getRadius() const { return mRadius; }

		private:
			float mRadius = 1.0f;
		};
	} // namespace Physics
} // namespace Orbital
