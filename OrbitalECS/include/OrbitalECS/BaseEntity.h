#ifndef OECS_INCLUDED
// Make sure the ECS headers are loaded in the correct order
#include "OrbitalECS/ECS.h"
#endif

#ifndef OBASEENTITY_INCLUDED
#define OBASEENTITY_INCLUDED

namespace Orbital
{
	namespace ECS
	{
		class BaseEntity
		{
		public:
			BaseEntity() : mRegistry(nullptr), mID()
			{
			}
			BaseEntity(Registry* registry, const EntityID& id) : mRegistry(registry), mID(id)
			{
			}
			BaseEntity(const BaseEntity& other) : mRegistry(other.mRegistry), mID(other.mID)
			{
			}

			template <typename T, typename... Args>
			Handle<T> push(Args... args)
			{
				return mRegistry->push<T>(mID, args...);
			}

			template <typename T>
			Handle<T> get() const
			{
				return mRegistry->get<T>(mID);
			}


			template <typename T>
			void remove()
			{
				mRegistry->remove<T>(mID);
			}

			void destroy()
			{
				mRegistry->deleteEntity(mID);
			}

			bool isValid() const
			{
				return mRegistry->isEntityValid(mID);
			}

			const EntityID& getID() const
			{
				return mID;
			}

			Registry* getRegistry() const
			{
				return mRegistry;
			}

		private:
			Registry* mRegistry;
			EntityID mID;
		};
	} // namespace ECS
} // namespace Orbital
#endif
