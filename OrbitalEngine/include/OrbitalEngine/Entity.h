#pragma once

#include "OrbitalECS/ECS.h"

namespace Orbital
{
	namespace Physics
	{
		class Transform;
	}
	using TransformComponent = Physics::Transform;
	class PhysicsComponent;
	class NativeScriptManager;

	class Entity
	{
	public:
		Entity() : mBaseEntity()
		{
		}

		Entity(const ECS::BaseEntity& e) : mBaseEntity(e)
		{
		}

		Entity(ECS::Registry* registry, const ECS::EntityID& id) : mBaseEntity(registry, id)
		{
		}

		Entity(const Entity& other) : mBaseEntity(other.mBaseEntity)
		{
		}

		template <typename T, typename... Args>
		ECS::Handle<T> push(Args... args)
		{
			assert(get<T>().isValid() == false && "Entity already has the requested component");

			if constexpr (std::is_same_v<PhysicsComponent, T>)
			{
				auto transform = get<TransformComponent>();
				auto physics = mBaseEntity.push<T>(T::Create(args...));

				if (transform.isValid())
				{
					// Setting the transform in the physics engine
					physics->setTransform(transform);
					// Removing the transform from the ECS
					mBaseEntity.remove<TransformComponent>();
				}

				return physics;
			}
			else
			{
				return mBaseEntity.push<T>(args...);
			}
		}

		ECS::Handle<PhysicsComponent> addPhysicsComponent() const;

		template <typename T>
		ECS::Handle<T> get() const
		{
			if constexpr(std::is_same_v<TransformComponent, T>)
			{
				return getTransform();
			}

			return mBaseEntity.get<T>();
		}

		ECS::Handle<TransformComponent> getTransform() const;

		template <typename T>
		void remove()
		{
			assert(get<T>().isValid() == true && "Trying to remove a non existing component");

			if constexpr(std::is_same_v<PhysicsComponent, T>)
			{
				return removePhysicsComponent();
			}
			else if constexpr(std::is_same_v<TransformComponent, T>)
			{
				return removeTransformComponent();
			}

			return mBaseEntity.remove<T>();
		}

		void removePhysicsComponent();
		void removeTransformComponent();

		void destroy()
		{
			mBaseEntity.destroy();
		}

	private:
		ECS::BaseEntity mBaseEntity;
	};
} // namespace Orbital
