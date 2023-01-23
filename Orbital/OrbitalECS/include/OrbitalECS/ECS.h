#ifndef OECS_INCLUDED
#define OECS_INCLUDED

#include "OrbitalECS/Context.h"

namespace Orbital::ECS
{
	using EntityID = UUID;
	class Registry;
} // namespace Orbital::ECS

#include "OrbitalECS/Containers.h"

#include "OrbitalECS/Handle.h"

#include "OrbitalECS/Registry.h"

#include "OrbitalECS/BaseEntity.h"

namespace Orbital::ECS
{
	// Handle IMPLEMENTATIONS
	template <typename T>
	auto Handle<T>::isValid() const -> bool
	{
		auto component = mRegistry->getPool<T>()->tryGet(mEntityID);

		if (component != nullptr)
			return true;
		else
			return false;
	}

	template <typename T>
	auto Handle<T>::operator*() -> T&
	{
		return *mRegistry->getPointer<T>(mEntityID);
	}

	template <typename T>
	auto Handle<T>::operator->() -> T*
	{
		return mRegistry->getPointer<T>(mEntityID);
	}

	template <typename T>
	auto Handle<T>::operator*() const -> const T&
	{
		return *mRegistry->getPointer<T>(mEntityID);
	}

	template <typename T>
	auto Handle<T>::operator->() const -> const T*
	{
		return mRegistry->getPointer<T>(mEntityID);
	}

	// TemporaryHandle IMPLEMENTATIONS
	template <typename T>
	auto TemporaryHandle<T>::isValid() const -> bool
	{
		auto component = mRegistry->getPool<T>()->tryGet(mEntityID);

		if (component != nullptr && component == mObject)
			return true;
		else
			return false;
	}

	template <typename T>
	auto TemporaryHandle<T>::operator*() -> T&
	{
		return *mObject;
	}

	template <typename T>
	auto TemporaryHandle<T>::operator->() -> T*
	{
		return mObject;
	}

	template <typename T>
	auto TemporaryHandle<T>::operator*() const -> const T&
	{
		return *mObject;
	}

	template <typename T>
	auto TemporaryHandle<T>::operator->() const -> const T*
	{
		return mObject;
	}
} // namespace Orbital::ECS
#endif
