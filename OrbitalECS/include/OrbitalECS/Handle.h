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
		 * @brief Contains an EntityID that allows to request operations on the component
		 */
		template <typename T>
		class Handle
		{
		public:
			Handle(const Registry* reg) : mEntityID(0), mRegistry(reg)
			{
			}
			Handle(EntityID id, const Registry* reg) : mEntityID(id), mRegistry(reg)
			{
			}
			virtual ~Handle()
			{
			}

			T& operator*();
			T* operator->();
			const T& operator*() const;
			const T* operator->() const;

			bool isValid() const;

			inline const EntityID& getEntityID() const
			{
				return mEntityID;
			}

		private:
			EntityID mEntityID;
			const Registry* mRegistry;
		};

		/**
		 * @class TemporaryHandle
		 * @brief Contains a reference to the component.
		 */
		template <typename T>
		class TemporaryHandle
		{
		public:
			TemporaryHandle(const Registry* reg) : mObject(nullptr), mEntityID(0), mRegistry(reg)
			{
			}
			TemporaryHandle(const T* object, EntityID id, const Registry* reg) : mObject(object), mEntityID(id), mRegistry(reg)
			{
			}
			virtual ~TemporaryHandle()
			{
			}

			T& operator*();
			T* operator->();
			const T& operator*() const;
			const T* operator->() const;

			bool isValid() const;

			inline const EntityID& getEntityID() const
			{
				return mEntityID;
			}

		private:
			T* mObject = nullptr;
			EntityID mEntityID = 0;
			const Registry* mRegistry;
		};
	} // namespace ECS
} // namespace Orbital
#endif
