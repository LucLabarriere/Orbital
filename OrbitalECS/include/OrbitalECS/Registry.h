#ifndef OECS_INCLUDED
// Make sure the ECS headers areloaded in the correct order
#include "OrbitalECS/ECS.h"
#endif

#ifndef OREGISTRY_INCLUDED
#define OREGISTRY_INCLUDED
namespace Orbital
{
	class BaseEntity;

	/**
	 * @class Registry
	 * @brief Stores the component pools
	 *
	 */
	class OECS_API Registry
	{
	public:
		Registry()
		{
		}
		~Registry()
		{
			LOGFUNC();
			if (!mCleaned)
			{
				Logger::Error("Error, the registry was not cleaned before closing the app");
				cleanUp();
			}
		}

		/**
		 * @brief deletes all pools
		 * Releases the memory so that the registry is unusable after, unleast registerComponentType is called again
		 */
		inline void cleanUp()
		{
			assert(!mCleaned);
			for (auto& [id, pool] : mPools)
			{
				delete pool;
			}

			for (auto& [id, pool] : mDerivationPools)
			{
				pool->clear();
				delete pool;
			}

			mCleaned = true;
		}

		/**
		 * @brief Removes all components and entities
		 */
		inline void reset()
		{
			for (auto& [id, pool] : mPools)
			{
				pool->clear();
			}

			for (auto& [id, pool] : mDerivationPools)
			{
				pool->clear();
			}

			mEntities.clear();
		}

		/**
		 * @brief Registers the type T in the ECS Registry
		 *
		 * @tparam T
		 */
		template <typename T>
		inline void registerComponentType()
		{
			Pool<T>* pool = new Pool<T>();

			mPools.insert({ typeid(T).hash_code(), static_cast<BasePool*>(pool) });
		}

		template <typename T>
		inline void registerDerivableComponentType()
		{
			DerivationPool<T>* pool = new DerivationPool<T>();

			mDerivationPools.insert({ typeid(T).hash_code(), static_cast<BasePool*>(pool) });
		}

		/**
		 * @brief Creates an entity
		 *
		 * @return Entity
		 */
		BaseEntity createEntity();

		void deleteEntity(const EntityID& id);

		/**
		 * @brief returns the entity of EntityID id
		 *
		 * @param id the UUID of the entity
		 * @return Entity
		 */
		BaseEntity getEntity(const EntityID& id);

		/**
		 * @brief Returns the corresponding pool, correctly casted
		 *
		 * @tparam T
		 * @return Pool<T>*
		 */
		template <typename T>
		Pool<T>* getPool() const
		{
			auto it = mPools.find(typeid(T).hash_code());
			assert(it != mPools.end());

			return static_cast<Pool<T>*>(it->second);
		}

		template <typename T>
		DerivationPool<T>* getDerivationPool() const
		{
			auto it = mDerivationPools.find(typeid(T).hash_code());
			assert(it != mDerivationPools.end());

			return static_cast<DerivationPool<T>*>(it->second);
		}

		/**
		 * @brief Returns the corresponding pool, uncasted
		 *
		 * @tparam T
		 * @return BasePool*
		 */
		template <typename T>
		BasePool* getBasePool() const
		{
			return mPools.find(typeid(T).hash_code())->second;
		}

		template <typename T>
		BasePool* getBaseDerivationPool() const
		{
			return mDerivationPools.find(typeid(T).hash_code())->second;
		}

		/**
		 * @brief Creates the component in place
		 *
		 * @param args The arguments required to build the component
		 * @return ComponentHandle<T>
		 */
		template <typename T, typename... Args>
		ComponentHandle<T> push(const EntityID& id, Args... args)
		{
			auto* pool = getPool<T>();
			auto& object = pool->push(id, args...);
			return ComponentHandle<T>(&object, id, this);
		}

		template <typename Base, typename T, typename... Args>
		ComponentHandle<T> push(const EntityID& id, Args... args)
		{
			DerivationPool<Base>* pool = getDerivationPool<Base>();
			auto object = pool->template pushDerived<T>(id, args...);
			return ComponentHandle<T>(object, id, this);
		}

		/**
		 * @brief Returns the requested Component
		 *
		 * @tparam T
		 * @param id
		 * @return Handle<T>
		 */
		template <typename T>
		ComponentHandle<T> get(const EntityID& id) const
		{
			Pool<T>* pool = getPool<T>();
			return ComponentHandle<T>(pool->tryGet(id), id, this);
		}

		template <typename Base, typename T>
		ComponentHandle<T> get(const EntityID& id) const
		{
			DerivationPool<Base>* pool = getDerivationPool<Base>();
			return ComponentHandle<T>(pool->template tryGet<T>(id), id, this);
		}

		template <typename T>
		void remove(const EntityID& id)
		{
			Pool<T>* pool = getPool<T>();
			pool->remove(id);
		}

		template <typename Base, typename T>
		void remove(const EntityID& id)
		{
			DerivationPool<Base>* pool = getDerivationPool<Base>();
			pool->remove(id);
		}

		template <typename T>
		std::unordered_map<EntityID, T>& components()
		{
			return getPool<T>()->components();
		}

		template <typename T>
		std::unordered_map<EntityID, T*>& derivedComponents()
		{
			return getDerivationPool<T>()->components();
		}

		bool isEntityValid(const EntityID id) const
		{
			return mEntities.find(id) == mEntities.end() ? false : true;
		}

	private:
		std::unordered_map<std::size_t, BasePool*> mPools;
		std::unordered_map<std::size_t, BasePool*> mDerivationPools;
		std::unordered_set<UUID> mEntities;
		bool mCleaned = false;
	};
} // namespace Orbital
#endif
