#pragma once

#include "OrbitalPhysics/Context.h"
#include "OrbitalPhysics/Transform.h"

namespace Orbital
{
	namespace Physics
	{
		using SupportFunction = std::function<Maths::Vec3(const Maths::Vec3& direction)>;

		class PointCollider;
		class SphereCollider;

		struct CollisionData
		{
			std::function<void()> trigger = [](){ Logger::Debug("Triggering"); };
			bool collide = false;
		};

		class OPHYSICS_API Collider
		{
		public:
			Collider(){};
			Collider(const Maths::Vec3& position) : mTransform({ .position = position }){};

			virtual CollisionData checkCollision(const Collider& collider) const = 0;
			virtual CollisionData checkCollision(const PointCollider& collider) const = 0;
			virtual CollisionData checkCollision(const SphereCollider& collider) const = 0;
			//virtual CollisionData checkCollision(const GJKCollider& collider) const = 0;

			virtual Maths::Vec3 supportFunction(const Maths::Vec3& direction) const
			{
				return mTransform.position;
			};

			inline const Transform& getTransform() const
			{
				return mTransform;
			}

			inline Transform& getTransform()
			{
				return mTransform;
			}

			inline void setTransform(const Physics::Transform& transform)
			{
				mTransform = transform;
			}

		protected:
			Transform mTransform;
		};
	} // namespace Physics
} // namespace Orbital
