#pragma once

#include "OrbitalEngine/Context.h"

namespace Orbital
{
	class ORBITAL_ENGINE_API Component
	{
	public:
		struct InitArgs
		{
			EntityID entityID;
			WeakRef<ECSManager> manager;
		};

		Component(const InitArgs& args);

		[[nodiscard]] auto getEntityID() const -> const EntityID& { return mEntityID; }
		[[nodiscard]] auto getEntity() const -> Entity;

	protected:
		EntityID mEntityID = 0;
		WeakRef<ECSManager> mManager;
	};
} // namespace Orbital
