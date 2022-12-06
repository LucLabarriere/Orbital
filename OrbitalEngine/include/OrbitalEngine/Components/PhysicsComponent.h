#pragma once

#include "OrbitalEngine/Components/TransformComponent.h"
#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/ECS/Handle.h"
#include "OrbitalPhysics/Colliders/Collider.h"
#include "OrbitalPhysics/Engine.h"

namespace Orbital
{
	enum class ColliderType
	{
		POINT_COLLIDER = 0,
		SPHERE_COLLIDER,
	};

	class PhysicsComponent
	{
	public:
		PhysicsComponent(PhysicsComponent&& other) : mCollider(other.mCollider)
		{
		}
		PhysicsComponent(const PhysicsComponent& other) : mCollider(other.mCollider)
		{
		}

		inline std::shared_ptr<Physics::Collider> getCollider()
		{
			return mCollider;
		}
		inline TransformComponent& getTransform()
		{
			return mCollider->getTransform();
		}
		inline void setTransform(const TransformComponent& transform)
		{
			mCollider->setTransform(transform);
		}

		static PhysicsComponent Create(Physics::Engine& engine, const ColliderType& colliderType);

	private:
		PhysicsComponent(const std::shared_ptr<Physics::Collider>& collider) : mCollider(collider){};

		std::shared_ptr<Physics::Collider> mCollider = nullptr;
	};

	using PhysicsHandle = SafeHandle<PhysicsComponent>;

	// SafeHandle IMPLEMENTATIONS
	template <>
	const TransformComponent& SafeHandle<TransformComponent>::operator*() const;
	template <>
	bool SafeHandle<TransformComponent>::isValid() const;
} // namespace Orbital
