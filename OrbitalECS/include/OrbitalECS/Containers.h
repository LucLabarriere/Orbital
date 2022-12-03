#ifndef OECS_INCLUDED
// Make sure the ECS headers areloaded in the correct order
#include "OrbitalECS/ECS.h"
#endif

#ifndef OCONTAINERS_INCLUDED
#define OCONTAINERS_INCLUDED

namespace Orbital
{
	namespace ECS
	{
		/**
		 * @class Pool
		 * @brief Contains all components of type T
		 */

		class BasePool
		{
		public:
			BasePool()
			{
			}
			virtual ~BasePool()
			{
			}

			virtual void clear() = 0;
			virtual void tryRemove(const EntityID& id) = 0;
		};

		template <typename T>
		class Pool : public BasePool
		{
		public:
			Pool() : BasePool()
			{
			}
			virtual ~Pool() override
			{
			}

			/**
			 * @brief Creates a component inplace and returns a reference to it
			 *
			 * @tparam Args
			 * @param id
			 * @param args
			 * @return T&
			 */
			template <typename... Args>
			T& push(const EntityID id, Args... args)
			{
				return mObjects.try_emplace(id, args...).first->second;
			}

			/**
			 * @brief Returns the component matching the EntityID
			 *
			 * @param id
			 * @return
			 */
			T* tryGet(const EntityID& id)
			{
				auto object = mObjects.find(id);

				if (object != mObjects.end())
					return &object->second;
				else
					return nullptr;
			}

			void remove(const EntityID id)
			{
				auto object = mObjects.find(id);
				assert(object != mObjects.end());
				mObjects.erase(id);
			}

			virtual void tryRemove(const EntityID& id) override
			{
				auto object = mObjects.find(id);
				if (object != mObjects.end())
					mObjects.erase(id);
			}

			virtual void clear() override
			{
				mObjects.clear();
			}

			std::unordered_map<EntityID, T>& components()
			{
				return mObjects;
			}

		private:
			std::unordered_map<EntityID, T> mObjects;
		};
	} // namespace ECS
} // namespace Orbital
#endif
