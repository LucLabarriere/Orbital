#pragma once

#include "OrbitalEngine/Context.h"

namespace Orbital
{
	class ECSManager;
	class Entity;

	class OENGINE_API Component
	{
	public:
		Component(const EntityID& entityID, const WeakRef<ECSManager>& manager);

		inline const EntityID& getEntityID() const { return mEntityID; }
		Entity getEntity() const;

	protected:
		const EntityID mEntityID = 0;
		WeakRef<ECSManager> mManager;
	};
} // namespace Orbital
