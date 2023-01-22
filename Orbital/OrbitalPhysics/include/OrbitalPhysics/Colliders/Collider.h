#pragma once

#include "OrbitalPhysics/Context.h"
#include "OrbitalPhysics/Transform.h"

namespace Orbital
{
	namespace Physics
	{
		using ColliderID = Orbital::UUID;

		enum class ColliderType
		{
			Point = 0,
			Sphere,
		};

		class Collider;
		class PointCollider;
		class SphereCollider;

		using CollisionCallback = std::function<void(Collider& self, Collider& other)>;
		using SupportFunction = std::function<Maths::Vec3(const Maths::Vec3& direction)>;

		struct CollisionData
		{
			Collider* A;
			Collider* B;
			bool collide = false;
		};

		class ORBITAL_PHYSICS_API Collider
		{
		public:
			Collider(const ColliderID& id, const ColliderType& type)
				: mID(id), mType(type){};
			Collider(
				const ColliderID& id, const ColliderType& type, const Transform& transform
			)
				: mID(id), mType(type), mTransform(transform){};

			Collider(const Collider& other) = delete;
			Collider(Collider&& other) = delete;

			virtual ~Collider(){};

			virtual auto checkCollision(Collider& collider) -> CollisionData = 0;
			virtual auto checkCollision(PointCollider& collider) -> CollisionData = 0;
			virtual auto checkCollision(SphereCollider& collider) -> CollisionData = 0;
			// virtual CollisionData checkCollision(const GJKCollider& collider) const =
			// 0;

			virtual auto supportFunction(const Maths::Vec3& direction) const
				-> Maths::Vec3
			{
				return mTransform.position;
			};

			inline auto getTransform() const -> const Transform& { return mTransform; }

			inline auto getTransform() -> Transform& { return mTransform; }

			inline void setTransform(const Physics::Transform& transform)
			{
				mTransform = transform;
			}

			inline auto getColliderType() const -> const ColliderType& { return mType; }

			inline void setCollisionCallback(const CollisionCallback& callback)
			{
				mOnCollide = callback;
			}

			inline void triggerCollisionCallback(Collider& other)
			{
				mOnCollide(*this, other);
			}
			inline auto getID() const -> const ColliderID& { return mID; }

		protected:
			ColliderID mID;
			ColliderType mType;
			CollisionCallback mOnCollide = [](Collider& self, Collider& other) {};
			Transform mTransform;
		};
	} // namespace Physics
} // namespace Orbital
