#pragma once

#include "OrbitalECS/ECS.h"

namespace Orbital
{
	class Collider;

	class Entity
	{
	public:
		Entity() : mBaseEntity()
		{
		}

		Entity(const BaseEntity& e) : mBaseEntity(e)
		{
		}

		Entity(Registry* registry, const EntityID& id) : mBaseEntity(registry, id)
		{
		}

		Entity(const Entity& other) : mBaseEntity(other.mBaseEntity)
		{
		}

		template <typename T, typename... Args>
		ComponentHandle<T> push(Args... args)
		{
			if constexpr (std::is_base_of<Collider, T>::value)
			{
				return mBaseEntity.push<Collider, T>(args...);
			}
			return mBaseEntity.push<T>(args...);
		}

		template <typename T>
		ComponentHandle<T> get() const
		{
			if constexpr (std::is_base_of<Orbital::Collider, T>::value)
			{
				auto component = mBaseEntity.get<Orbital::Collider, T>();
				return component;
			}
			auto component = mBaseEntity.get<T>();
			return component;
		}

		template <typename T>
		void remove()
		{
			if constexpr (std::is_base_of<Orbital::Collider, T>::value)
			{
				return mBaseEntity.remove<Orbital::Collider, T>();
			}
			return mBaseEntity.remove<T>();
		}

		void destroy()
		{
			mBaseEntity.destroy();
		}

	private:
		BaseEntity mBaseEntity;
	};
} // namespace Orbital
