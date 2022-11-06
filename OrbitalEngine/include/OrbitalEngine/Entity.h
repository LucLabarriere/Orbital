#pragma once

#include "OrbitalECS/ECS.h"

namespace Orbital
{
	class Collider2DComponent;
	class Collider3DComponent;

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
			if constexpr (std::is_base_of<Collider2DComponent, T>::value)
			{
				return mBaseEntity.push<Collider2DComponent, T>(args...);
			}
			else if constexpr (std::is_base_of<Collider3DComponent, T>::value)
			{
				return mBaseEntity.push<Collider3DComponent, T>(args...);
			}
			return mBaseEntity.push<T>(args...);
		}

		template <typename T>
		ComponentHandle<T> get() const
		{
			if constexpr (std::is_base_of<Collider2DComponent, T>::value)
			{
				return mBaseEntity.get<Collider2DComponent, T>();
			}
			else if constexpr (std::is_base_of<Collider3DComponent, T>::value)
			{
				return mBaseEntity.get<Collider3DComponent, T>();
			}
			return mBaseEntity.get<T>();
		}

		template <typename T>
		void remove()
		{
			if constexpr (std::is_base_of<Orbital::Collider2DComponent, T>::value)
			{
				return mBaseEntity.remove<Orbital::Collider2DComponent, T>();
			}
			else if constexpr (std::is_base_of<Orbital::Collider3DComponent, T>::value)
			{
				return mBaseEntity.remove<Orbital::Collider3DComponent, T>();
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
