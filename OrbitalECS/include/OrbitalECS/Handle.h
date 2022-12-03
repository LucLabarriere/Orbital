#ifndef OECS_INCLUDED
// Make sure the ECS headers are loaded in the correct order
#include "OrbitalECS/ECS.h"
#endif

#ifndef OHANDLE_INCLUDED
#define OHANDLE_INCLUDED

namespace Orbital
{
	namespace ECS
	{
		/**
		 * @class Handle
		 * @brief Contains a pointer to the object and its EntityID
		 */
		template <typename T>
		class Handle
		{
		public:
			Handle(const Registry* reg) : mObject(nullptr), mEntityID(0), mRegistry(reg)
			{
			}
			Handle(T* object, EntityID id, const Registry* reg)
				: mObject(object), mEntityID(id), mRegistry(reg)
			{
			}
			virtual ~Handle()
			{
			}

			inline T* operator->()
			{
				return mObject;
			}
			inline T& operator*()
			{
				return *mObject;
			}
			inline const T* operator->() const
			{
				return mObject;
			}
			inline const T& operator*() const
			{
				return *mObject;
			}
			bool isValid() const;

			inline const EntityID& getEntityID() const
			{
				return mEntityID;
			}

		private:
			T* mObject;
			EntityID mEntityID;
			const Registry* mRegistry;
		};
	} // namespace ECS
} // namespace Orbital
#endif
