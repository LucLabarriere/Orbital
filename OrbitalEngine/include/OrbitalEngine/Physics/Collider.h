#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/Components/DynamicsComponent.h"
#include "OrbitalEngine/Components/TransformComponent.h"
#include "OrbitalEngine/Entity.h"

namespace Orbital
{
	struct CollisionPoints
	{
		Maths::Vec3 A = { 0.0f, 0.0f, 0.0f };
		Maths::Vec3 B = { 0.0f, 0.0f, 0.0f };
		Maths::Vec3 vector = { 0.0f, 0.0f, 0.0f };
		Maths::Vec3 normal = { 0.0f, 0.0f, 0.0f };
		float distance = 0.0f;
		bool collide = false;
	};

	struct Collision
	{
		Entity A;
		Entity B;
		CollisionPoints points;
	};

	class PlaneCollider;
	class SphereCollider;

	enum class ColliderType
	{
		Static = 0,
		Kinetimatic = 0,
		Dynamic
	};

	class Collider
	{
	public:
		Collider(const TransformHandle& transform)
			: mTransform(transform), mDynamics(nullptr), mColliderType(ColliderType::Static)
		{
		}

		Collider(const TransformHandle& transform, const DynamicsHandle& dynamics)
			: mTransform(transform), mDynamics(dynamics)
		{
		}

		inline const TransformHandle& getTransform() const
		{
			return mTransform;
		}

		inline const std::string& getType() const
		{
			return mType;
		}

		virtual CollisionPoints getCollisionPoints(const Collider& other) const
		{
			return {};
		};
		virtual CollisionPoints getCollisionPoints(const PlaneCollider& other) const
		{
			return {};
		};
		virtual CollisionPoints getCollisionPoints(const SphereCollider& other) const
		{
			return {};
		};

		ColliderType getColliderType() const { return mColliderType; }
		void setColliderType(ColliderType t) { mColliderType = t; }

		bool isTrigger() const { return mTrigger; }
		void trigger() const { mOnTriggerEnter(); }

	protected:
		TransformHandle mTransform;
		DynamicsHandle mDynamics;
		std::function<void()> mOnTriggerEnter = [](){ };
		std::function<void()> mOnTriggerLeave = [](){ };

		bool mTrigger = true;
		bool mTriggering = false;
		ColliderType mColliderType = ColliderType::Dynamic;

		std::string mType = "";
	};
} // namespace Orbital
