#pragma once

#include "OrbitalECS/Context.h"
#include "OrbitalECS/Handle.h"
#include "OrbitalTools/UUID.h"

namespace Orbital
{
	template <typename T>
	class Pool
	{
	public:
		Pool() { }

		template <typename ...Args>
		T& Create(const UUID& entity, Args... args)
		{
			mObjects.emplace(entity, T(args...));

			return mObjects[entity];
		}

		void Delete(const UUID& entity)
		{
			mObjects.erase(entity);
		}

		T* Get(const UUID& entity)
		{
			auto result = mObjects.find(entity);

			if (result != mObjects.end())
				return &result->second;

			return nullptr;
		}

		void Print() const
		{
			unsigned nbuckets = mObjects.bucket_count();

			std::cout << "mObjects has " << nbuckets << " buckets:\n";

			for (unsigned i = 0; i < nbuckets; ++i) {
				std::cout << "bucket #" << i << " has " << mObjects.bucket_size(i) << " elements.\n";
			}
		}

		std::unordered_map<UUID, T>::iterator begin() { return mObjects.begin(); }
		std::unordered_map<UUID, T>::iterator end() { return mObjects.end(); }

	private:
		std::unordered_map<UUID, T> mObjects;
	};

	class PoolRepresentation
	{
	public:
		PoolRepresentation() { }
		PoolRepresentation(void* poolPtr) : mPoolPtr(poolPtr) { }

		void Delete()
		{
			delete mPoolPtr;
		}

		template <typename T>
		Pool<T>& Get() const
		{
			return *(Pool<T>*)mPoolPtr;
		}

	private:
		void* mPoolPtr = nullptr;
	};
}