#ifndef OECS_INCLUDED
// Make sure the ECS headers are loaded in the correct order
#include "OrbitalECS/ECS.h"
#endif

#ifndef OHANDLE_INCLUDED
#define OHANDLE_INCLUDED

namespace Orbital::ECS
{
	/**
	 * @class Handle
	 * @brief Contains an EntityID that allows to request operations on the component
	 */
	template <typename T>
	class Handle
	{
	public:
		Handle(const Registry* reg) : mEntityID(0), mRegistry(reg){};
		Handle(EntityID id, const Registry* reg) : mEntityID(id), mRegistry(reg){};
		virtual ~Handle() = default;

		auto operator*() -> T&;
		auto operator->() -> T*;
		auto operator*() const -> const T&;
		auto operator->() const -> const T*;

		[[nodiscard]] auto isValid() const -> bool;
		[[nodiscard]] auto getEntityID() const -> const EntityID& { return mEntityID; }

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
		TemporaryHandle(const Registry* reg)
			: mObject(nullptr), mEntityID(0), mRegistry(reg){};
		TemporaryHandle(const T* object, EntityID id, const Registry* reg)
			: mObject(object), mEntityID(id), mRegistry(reg){};
		virtual ~TemporaryHandle() = default;

		auto operator*() -> T&;
		auto operator->() -> T*;
		auto operator*() const -> const T&;
		auto operator->() const -> const T*;

		[[nodiscard]] auto isValid() const -> bool;
		[[nodiscard]] auto getEntityID() const -> const EntityID& { return mEntityID; }

	private:
		T* mObject = nullptr;
		EntityID mEntityID = 0;
		const Registry* mRegistry;
	};
} // namespace Orbital::ECS
#endif
