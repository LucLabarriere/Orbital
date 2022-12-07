#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/ECS/Components/TransformComponent.h"
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

	class OENGINE_API PhysicsComponent
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
} // namespace Orbital