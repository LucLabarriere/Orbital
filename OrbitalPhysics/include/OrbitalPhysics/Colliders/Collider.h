#pragma once

#include "OrbitalPhysics/Context.h"

namespace Orbital
{
	namespace Physics
	{
		using SupportFunction = std::function<Maths::Vec3(const Maths::Vec3& direction)>;

		class PointCollider;
		class SphereCollider;

		struct CollisionData
		{
			bool collide = false;
		};

		class OPHYSICS_API Collider
		{
		public:
			Collider(){};
			Collider(const Maths::Vec3& position) : mPosition(position){};

			virtual CollisionData checkCollision(const Collider& collider) const = 0;
			virtual CollisionData checkCollision(const PointCollider& collider) const = 0;
			virtual CollisionData checkCollision(const SphereCollider& collider) const = 0;

			virtual Maths::Vec3 supportFunction(const Maths::Vec3& direction) const
			{
				return mPosition;
			};

			inline const Maths::Vec3& getPosition() const
			{
				return mPosition;
			}

		protected:
			Maths::Vec3 mPosition = { 0.0f, 0.0f, 0.0f };
		};
	} // namespace Physics
} // namespace Orbital
