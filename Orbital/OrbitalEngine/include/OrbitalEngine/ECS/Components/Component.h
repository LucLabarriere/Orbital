#pragma once

#include "OrbitalEngine/Context.h"

namespace Orbital
{
	class ECSManager;
	class Entity;

	class OENGINE_API Component
	{
	public:
		struct InitArgs
		{
			EntityID entityID;
			WeakRef<ECSManager> manager;
		};

		Component(const InitArgs& args);

		inline const EntityID& getEntityID() const { return mEntityID; }
		Entity getEntity() const;

	protected:
		EntityID mEntityID = 0;
		WeakRef<ECSManager> mManager;
	};
} // namespace Orbital
