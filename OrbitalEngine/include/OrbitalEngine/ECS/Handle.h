#pragma once
#include "OrbitalEngine/Context.h"

namespace Orbital
{
	class ECSManager;
	using EntityID = UUID;
	template <typename T>
	class TemporaryHandle;

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
		SafeHandle(const std::weak_ptr<ECSManager>& manager) : mManager(manager){};
		SafeHandle(const EntityID& id, const std::weak_ptr<ECSManager>& man) : mEntityID(id), mManager(man){};
		SafeHandle(const SafeHandle& other) : mEntityID(other.mEntityID), mManager(other.mManager){};
		virtual ~SafeHandle(){};

		T& operator*();
		T* operator->();
		const T& operator*() const;
		const T* operator->() const;
		const TemporaryHandle<T> getTemporary() const;
		TemporaryHandle<T> getTemporary();

		bool isValid() const;

		inline const EntityID& getEntityID() const
		{
			return mEntityID;
		}

	private:
		EntityID mEntityID = 0;
		std::weak_ptr<ECSManager> mManager;
	};

	/**
	 * @class TemporaryHandle
	 * @brief Contains a reference to the component.
	 * Its use is unsafe and it should be used only when it is 100% sure that no
	 * memory reorganization occurs
	 */
	template <typename T>
	class TemporaryHandle
	{
	public:
		TemporaryHandle(const std::weak_ptr<ECSManager>& man) : mObject(nullptr), mEntityID(0), mManager(man)
		{
		}
		TemporaryHandle(T* object, const EntityID& id, const std::weak_ptr<ECSManager>& man)
			: mObject(object), mEntityID(id), mManager(man)
		{
		}
		virtual ~TemporaryHandle()
		{
		}

		const T& operator*() const;
		const T* operator->() const;
		T& operator*();
		T* operator->();

		bool isValid() const;

		inline const EntityID& getEntityID() const
		{
			return mEntityID;
		}

	private:
		T* mObject = nullptr;
		EntityID mEntityID = 0;
		std::weak_ptr<ECSManager> mManager;
	};
} // namespace Orbital

#include "OrbitalEngine/ECS/ECSManager.h"
