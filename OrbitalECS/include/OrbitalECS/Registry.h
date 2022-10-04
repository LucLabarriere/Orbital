#pragma once

#include "OrbitalECS/Context.h"
#include "OrbitalECS/Pool.h"
#include "OrbitalTools/UUID.h"
#include "OrbitalECS/EntityHandle.h"
#include <typeindex>

namespace Orbital
{

	using EntityID = UUID;

	class OECS_API Registry
	{
	public:
		~Registry()
		{
			for (auto& [typeId, pool] : mPools)
				pool.Delete();
		}

		EntityID Create()
		{
			return mEntities.emplace().first->Copy();
		}

		template <typename T, typename ...Args>
		Handle<T> AddComponent(const EntityID& entity, Args... args)
		{
			size_t componentId = typeid(T).hash_code();
			Pool<T>& pool = mPools[componentId].Get<T>();
			auto& component = pool.Create(entity, args...);
			return Handle<T>(entity, &component);
			return Handle<T>();
		}

		template <typename T>
		void DeleteComponent(const EntityID& entity)
		{
			size_t componentId = typeid(T).hash_code();
			Pool<T>& pool = mPools[componentId].Get<T>();
			pool.Delete(entity);
		}

		template <typename T>
		Handle<T> GetComponent(const EntityID& entity)
		{
			if (mEntities.find(entity) != mEntities.end())
			{
				size_t componentId = typeid(T).hash_code();
				Pool<T>& pool = mPools[componentId].Get<T>();
				T* component = pool.Get(entity);
				return Handle<T>(entity, component);
			}

			return Handle<T>();
		}

		template <typename T>
		Pool<T>& Components()
		{
			size_t componentId = typeid(T).hash_code();
			return mPools[componentId].Get<T>();
		}

		template <typename T>
		void RegisterType()
		{
			size_t componentId = typeid(T).hash_code();
			mPools.emplace(componentId, PoolRepresentation(new Pool<T>()));
		}

		bool IsValid(const EntityID& entityID) const
		{
			return mEntities.find(entityID) != mEntities.end();
		}

		void DeleteEntity(const EntityID& entityID)
		{
			mEntities.erase(entityID);
		}

		std::unordered_set<EntityID>& Entities()
		{
			return mEntities;
		}

	private:
		std::unordered_map<size_t, PoolRepresentation> mPools;
		std::unordered_set<EntityID> mEntities;
	};
}