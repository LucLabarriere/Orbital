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
		template <typename T>
		using ComponentContainer = std::map<ECS::EntityID, T>;

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
			T& push(const EntityID id, Args&&... args)
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
				Orbital::Assert(object != mObjects.end(), "The entity does not have this component");
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

			ComponentContainer<T>& components()
			{
				return mObjects;
			}

		private:
			ComponentContainer<T> mObjects;
		};
	} // namespace ECS
} // namespace Orbital
#endif
