#ifndef OECS_INCLUDED
// Make sure the ECS headers are loaded in the correct order
#include "OrbitalECS/ECS.h"
#endif

#ifndef OHANDLE_INCLUDED
#define OHANDLE_INCLUDED
namespace Orbital
{
	/**
	 * @class ComponentHandle
	 * @brief Contains a pointer to the object and its EntityID
	 */
	template <typename T>
	class ComponentHandle
	{
	public:
		ComponentHandle(const Registry* reg) : mObject(nullptr), mEntityID(0), mRegistry(reg)
		{
		}
		ComponentHandle(T* object, EntityID id, const Registry* reg) : mObject(object), mEntityID(id), mRegistry(reg)
		{
		}
		virtual ~ComponentHandle()
		{
		}

		template <typename S>
		static ComponentHandle<S> Cast(const ComponentHandle<T>& other)
		{
			ComponentHandle<S> handle(static_cast<S*>(other.mObject), other.mEntityID, other.mRegistry);
			return handle;
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
} // namespace Orbital
#endif
