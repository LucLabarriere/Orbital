#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/Services.h"
#include "OrbitalEngine/Services/ServiceInterface.h"

namespace Orbital
{
	namespace Physics
	{
		class Engine;
	}

	class ORBITAL_ENGINE_API PhysicsEngineInterface: public ServiceInterface
	{
	public:
		PhysicsEngineInterface();
		PhysicsEngineInterface(const SharedApplication& app);
		void InitializeInterface();

		void ClearComponents();
		void ClearComponents(const EntityID& id);
		WeakRef<Physics::Engine> Get() const { return mInstance; }

	private:
		WeakRef<Physics::Engine> mInstance;
	};

	OCREATE_SERVICE(PhysicsEngine);

} // namespace Orbital
