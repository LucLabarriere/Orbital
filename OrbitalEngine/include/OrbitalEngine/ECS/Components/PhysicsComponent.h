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
		PhysicsComponent(
			const Component::InitArgs& c, const WeakRef<Physics::Engine>& engine
		);
		PhysicsComponent(PhysicsComponent&& other) = default;
		PhysicsComponent(const PhysicsComponent& other) = default;

		/**
		 * @brief Get the collider uncasted
		 *
		 * @return Reference to the collider
		 */
		inline Physics::Collider& getCollider()
		{
			return mEngine.lock()->getCollider(mEntityID);
		}

		/**
		 * @brief Get the collider casted to the appropriate type
		 *
		 * @tparam T The collider type to cast the collider to (SphereCollider, PointCollider, etc.)
		 * @return Reference to the casted collider
		 */
		template <typename T>
		inline T& getCastedCollider()
		{
			return mEngine.lock()->getCastedCollider<T>(mEntityID);
		}

		/**
		 * @brief Get the transform
		 *
		 * @return Mutable reference to the transform
		 */
		inline TransformComponent& getTransform()
		{
			return getCollider().getTransform();
		}

		/**
		 * @brief Sets the transform
		 *
		 * @param transform
		 */
		inline void setTransform(const TransformComponent& transform)
		{
			getCollider().setTransform(transform);
		}

	private:
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
	OENGINE_API SafeHandle<PhysicsComponent> Entity::push<PhysicsComponent, Physics::ColliderType>(
		Physics::ColliderType&& colliderType
	);

	/**
	 * @brief Adds a PhysicsComponent
	 *
	 * If the entity has a MeshFilter, uses it to guess a ColliderType. If not, uses
	 * Physics::ColliderType::PointCollider;
	 *
	 * @return SafeHandle<PhysicsComponent>
	 */
	template <>
	OENGINE_API SafeHandle<PhysicsComponent> Entity::push<PhysicsComponent>();
} // namespace Orbital
