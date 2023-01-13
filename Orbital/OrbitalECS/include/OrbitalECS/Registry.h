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
			 * Releases the memory so that the registry is unusable after, unless registerComponentType is called again
			 */
			inline void cleanUp()
			{
				Orbital::Assert(!mCleaned, "The registry was already cleaned up");
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
				Logger::Debug("Registering component ", typeid(T).name());

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
			 * @todo Remake the error message so that no unnecessary operations are performed
			 *
			 * @tparam T
			 * @return Pool<T>*
			 */
			template <typename T>
			Pool<T>* getPool() const
			{
				auto it = mPools.find(typeid(T).hash_code());
				Orbital::Assert(
					it != mPools.end(),
					std::string("Did you forget to register the type ") + typeid(T).name() + "?"
				);

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
			Handle<T> push(const EntityID& id, Args&&... args)
			{
				auto* pool = getPool<T>();
				pool->push(id, std::move(args)...);
				return Handle<T>(id, this);
			}

			/**
			 * @brief Returns the requested Component
			 *
			 * @tparam T
			 * @param id
			 * @return ConstHandle<T>
			 */
			template <typename T>
			const Handle<T> get(const EntityID& id) const
			{
				return Handle<T>(id, this);
			}

			/**
			 * @brief Returns the requested Component
			 *
			 * @tparam T
			 * @param id
			 * @return Handle<T>
			 */
			template <typename T>
			Handle<T> get(const EntityID& id)
			{
				return Handle<T>(id, this);
			}

			template <typename T>
			T* getPointer(const EntityID& id) const
			{
				Pool<T>* pool = getPool<T>();
				return pool->tryGet(id);
			}

			template <typename T>
			T* getPointer(const EntityID& id)
			{
				Pool<T>* pool = getPool<T>();
				return pool->tryGet(id);
			}

			template <typename T>
			void remove(const EntityID& id)
			{
				Pool<T>* pool = getPool<T>();
				pool->remove(id);
			}

			template <typename T>
			ComponentContainer<T>& components()
			{
				return getPool<T>()->components();
			}

			std::unordered_set<UUID>& entities()
			{
				return mEntities;
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
