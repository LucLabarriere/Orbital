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
		SafeHandle(){};
		SafeHandle(const WeakRef<ECSManager>& manager) : mManager(manager){};
		SafeHandle(const EntityID& id, const WeakRef<ECSManager>& man)
			: mEntityID(id), mManager(man){};
		SafeHandle(const SafeHandle& other)
			: mEntityID(other.mEntityID), mManager(other.mManager){};
		virtual ~SafeHandle(){};

		auto get() -> T&;
		auto get() const -> const T&;
		T& operator*();
		auto operator->() -> T*;
		const T& operator*() const;
		auto operator->() const -> const T*;

		bool isValid() const;

		inline auto getEntityID() const -> const EntityID& { return mEntityID; }

	private:
		EntityID mEntityID = 0;
		WeakRef<ECSManager> mManager;
	};
} // namespace Orbital

#include "OrbitalEngine/ECS/ECSManager.h"
