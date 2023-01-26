#pragma once
#include "OrbitalEngine/Context.h"

namespace Orbital
{
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
		SafeHandle() = default;
		SafeHandle(const WeakRef<ECSManager>& manager) : mManager(manager){};
		SafeHandle(const EntityID& id, const WeakRef<ECSManager>& man)
			: mEntityID(id), mManager(man){};
		SafeHandle(const SafeHandle& other)
			: mEntityID(other.mEntityID), mManager(other.mManager){};
		virtual ~SafeHandle() = default;

		auto operator=(const SafeHandle<T>& other) -> SafeHandle<T>&
		{
			mEntityID = other.mEntityID;
			mManager = other.mManager;
			return *this;
		}

		auto get() -> T&;
		auto get() const -> const T&;
		auto operator*() -> T&;
		auto operator->() -> T*;
		auto operator*() const -> const T&;
		auto operator->() const -> const T*;

		[[nodiscard]] auto isValid() const -> bool;
		[[nodiscard]] auto getEntityID() const -> const EntityID& { return mEntityID; }

	private:
		EntityID mEntityID = 0;
		WeakRef<ECSManager> mManager{};
	};
} // namespace Orbital

#include "OrbitalEngine/ECS/ECSManager.h"
