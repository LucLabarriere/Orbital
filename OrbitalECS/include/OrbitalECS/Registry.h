#ifndef OECS_INCLUDED
// Make sure the ECS headers areloaded in the correct order
#include "OrbitalECS/ECS.h"
#endif

#ifndef OREGISTRY_INCLUDED
#define OREGISTRY_INCLUDED

namespace Orbital
{
	namespace ECS
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
				assert(it != mPools.end() && "Did you forget to register the type ?");

				return static_cast<Pool<T>*>(it->second);
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

			/**
			 * @brief Creates the component in place
			 *
			 * @param args The arguments required to build the component
			 * @return Handle<T>
			 */
			template <typename T, typename... Args>
			Handle<T> push(const EntityID& id, Args... args)
			{
				auto* pool = getPool<T>();
				auto& object = pool->push(id, args...);
				return Handle<T>(&object, id, this);
			}

			/**
			 * @brief Returns the requested Component
			 *
			 * @tparam T
			 * @param id
			 * @return Handle<T>
			 */
			template <typename T>
			Handle<T> get(const EntityID& id) const
			{
				Pool<T>* pool = getPool<T>();
				return Handle<T>(pool->tryGet(id), id, this);
			}

			template <typename T>
			void remove(const EntityID& id)
			{
				Pool<T>* pool = getPool<T>();
				pool->remove(id);
			}

			template <typename T>
			std::unordered_map<EntityID, T>& components()
			{
				return getPool<T>()->components();
			}

			bool isEntityValid(const EntityID id) const
			{
				return mEntities.find(id) == mEntities.end() ? false : true;
			}

		private:
			std::unordered_map<std::size_t, BasePool*> mPools;
			std::unordered_set<UUID> mEntities;
			bool mCleaned = false;
		};
	} // namespace ECS
} // namespace Orbital
#endif
