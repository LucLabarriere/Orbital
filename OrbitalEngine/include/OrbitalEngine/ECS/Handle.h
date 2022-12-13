#pragma once
#include "OrbitalEngine/Context.h"

namespace Orbital
{
	class ECSManager;

	/**
	 * @class SafeHandle
	 * @brief Contains an EntityID that allows to request operations on the component
	 * It is safe in the way that the component is requested for each operation
	 * in case it was moved in memory
	 */
	template <typename T>
	class SafeHandle
	{
	public:
		SafeHandle(const WeakRef<ECSManager>& manager) : mManager(manager){};
		SafeHandle(const EntityID& id, const WeakRef<ECSManager>& man) : mEntityID(id), mManager(man){};
		SafeHandle(const SafeHandle& other) : mEntityID(other.mEntityID), mManager(other.mManager){};
		virtual ~SafeHandle(){};

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
		EntityID mEntityID = 0;
		WeakRef<ECSManager> mManager;
	};
} // namespace Orbital

#include "OrbitalEngine/ECS/ECSManager.h"
