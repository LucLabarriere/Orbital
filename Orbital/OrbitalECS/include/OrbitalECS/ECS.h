#ifndef OECS_INCLUDED
#define OECS_INCLUDED

#include "OrbitalECS/Context.h"

namespace Orbital
{
	namespace ECS
	{
		using EntityID = UUID;
		class Registry;
	} // namespace ECS
} // namespace Orbital

#include "OrbitalECS/Containers.h"

#include "OrbitalECS/Handle.h"

#include "OrbitalECS/Registry.h"

#include "OrbitalECS/BaseEntity.h"

namespace Orbital
{
	namespace ECS
	{
		// Handle IMPLEMENTATIONS
		template <typename T>
		bool Handle<T>::isValid() const
		{
			auto component = mRegistry->getPool<T>()->tryGet(mEntityID);

			if (component != nullptr)
				return true;
			else
				return false;
		}

		template <typename T>
		T& Handle<T>::operator*()
		{
			return *mRegistry->getPointer<T>(mEntityID);
		}

		template <typename T>
		T* Handle<T>::operator->()
		{
			return mRegistry->getPointer<T>(mEntityID);
		}

		template <typename T>
		const T& Handle<T>::operator*() const
		{
			return *mRegistry->getPointer<T>(mEntityID);
		}

		template <typename T>
		const T* Handle<T>::operator->() const
		{
			return mRegistry->getPointer<T>(mEntityID);
		}

		// TemporaryHandle IMPLEMENTATIONS
		template <typename T>
		bool TemporaryHandle<T>::isValid() const
		{
			auto component = mRegistry->getPool<T>()->tryGet(mEntityID);

			if (component != nullptr && component == mObject)
				return true;
			else
				return false;
		}

		template <typename T>
		T& TemporaryHandle<T>::operator*()
		{
			return *mObject;
		}

		template <typename T>
		T* TemporaryHandle<T>::operator->()
		{
			return mObject;
		}

		template <typename T>
		const T& TemporaryHandle<T>::operator*() const
		{
			return *mObject;
		}

		template <typename T>
		const T* TemporaryHandle<T>::operator->() const
		{
			return mObject;
		}
	} // namespace ECS
} // namespace Orbital
#endif
