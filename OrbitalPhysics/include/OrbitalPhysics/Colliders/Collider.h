#pragma once

#include "OrbitalPhysics/Context.h"
#include "OrbitalPhysics/Transform.h"

namespace Orbital
{
	namespace Physics
	{
		enum class ColliderType
		{
			Point = 0,
			Sphere,
		};

		class Collider;
		class PointCollider;
		class SphereCollider;

		using CollisionCallback = std::function<void(const std::weak_ptr<Collider>& other)>;
		using SupportFunction = std::function<Maths::Vec3(const Maths::Vec3& direction)>;

		struct CollisionData
		{
			bool collide = false;
		};

		class OPHYSICS_API Collider
		{
		public:
			Collider(const ColliderType& type) : mType(type){};
			Collider(const ColliderType& type, const Transform& transform) : mType(type), mTransform(transform){};

			virtual CollisionData checkCollision(const Collider& collider) const = 0;
			virtual CollisionData checkCollision(const PointCollider& collider) const = 0;
			virtual CollisionData checkCollision(const SphereCollider& collider) const = 0;
			// virtual CollisionData checkCollision(const GJKCollider& collider) const = 0;

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

			inline const ColliderType& getColliderType() const
			{
				return mType;
			}

			inline void setCollisionCallback(const CollisionCallback& callback)
			{
				mOnCollide = callback;
			}

			inline void triggerCollisionCallback(const std::weak_ptr<Collider>& other) { mOnCollide(other); }

		protected:
			ColliderType mType;
			CollisionCallback mOnCollide = [](const std::weak_ptr<Collider>& other) {};

			Transform mTransform;
		};
	} // namespace Physics
} // namespace Orbital
