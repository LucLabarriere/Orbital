#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/ECS/Components/Component.h"
#include "OrbitalEngine/ECS/Components/TransformComponent.h"
#include "OrbitalEngine/ECS/Entity.h"
#include "OrbitalEngine/ECS/Handle.h"

#include "OrbitalPhysics/Colliders/Collider.h"
#include "OrbitalPhysics/Engine.h"

namespace Orbital
{
	class OENGINE_API PhysicsComponent : public Component
	{
	public:
		PhysicsComponent(PhysicsComponent&& other)
			: Component(other.mEntityID, other.mManager), mEngine(other.mEngine), mCollider(other.mCollider)
		{
		}
		PhysicsComponent(const PhysicsComponent& other)
			: Component(other.mEntityID, other.mManager), mEngine(other.mEngine), mCollider(other.mCollider)
		{
		}
		PhysicsComponent(
			const EntityID& entityID, const WeakRef<ECSManager>& manager, const WeakRef<Physics::Engine>& engine,
			const WeakRef<Physics::Collider>& collider
		)
			: Component(entityID, manager), mEngine(engine), mCollider(collider){};

		/**
		 * @brief Get the collider uncasted
		 *
		 * @return Weak pointer to the uncasted collider
		 */
		inline WeakRef<Physics::Collider> getCollider()
		{
			return mCollider;
		}

		/**
		 * @brief Get the collider casted to the appropriate type
		 *
		 * @tparam T The collider type to cast the collider to (SphereCollider, PointCollider, etc.)
		 * @return Weak pointer to the casted collider
		 */
		template <typename T>
		WeakRef<T> getCastedCollider()
		{
			return mEngine.lock()->cast<T>(mCollider);
		}

		/**
		 * @brief Get the transform
		 *
		 * @return Mutable reference to the transform
		 */
		inline TransformComponent& getTransform()
		{
			return mCollider.lock()->getTransform();
		}

		/**
		 * @brief Sets the transform
		 *
		 * @param transform
		 */
		inline void setTransform(const TransformComponent& transform)
		{
			mCollider.lock()->setTransform(transform);
		}

	private:
		WeakRef<Physics::Collider> mCollider;
		WeakRef<Physics::Engine> mEngine;
	};

	using PhysicsHandle = SafeHandle<PhysicsComponent>;

	/**
	 * @brief Adds a PhysicsComponent
	 *
	 * Pushes a PhysicsComponent to the entity using a ColliderType specifier.
	 * If the entity has a transform, copies it into the collider and removes the original one from the ECS pool
	 *
	 * @todo Find a way to pass const references

	 * @param colliderType : The collider type
	 * @return SafeHandle<PhysicsComponent>
	 */
	template <>
	OENGINE_API SafeHandle<PhysicsComponent> Entity::push<PhysicsComponent, Physics::ColliderType>(Physics::ColliderType colliderType);

	/**
	 * @brief Adds a PhysicsComponent
	 *
	 * If the entity has a MeshFilter, uses it to guess a ColliderType. If not, uses
	 * Physics::ColliderType::PointCollider;
	 *
	 * @param engine : The physics engine instance to store the collider
	 * @return SafeHandle<PhysicsComponent>
	 */
	template <>
	OENGINE_API SafeHandle<PhysicsComponent> Entity::push<PhysicsComponent>();
} // namespace Orbital
