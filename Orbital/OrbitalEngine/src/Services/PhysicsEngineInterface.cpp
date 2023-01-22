#include "OrbitalEngine/Services/PhysicsEngineInterface.h"
#include "OrbitalEngine/OrbitalApplication.h"

namespace Orbital
{
	PhysicsEngineInterface::PhysicsEngineInterface() : ServiceInterface()
	{
	}

	PhysicsEngineInterface::PhysicsEngineInterface(const SharedApplication& app)
		: ServiceInterface(app)
	{
	}

	void PhysicsEngineInterface::InitializeInterface()
	{
		mInstance = mApp.lock()->getPhysicsEngine();
	}

	void PhysicsEngineInterface::ClearComponents()
	{
		mInstance.lock()->clearColliders();
	}

	void PhysicsEngineInterface::ClearComponents(const EntityID& id)
	{
		mInstance.lock()->clearColliders(id);
	}

} // namespace Orbital
