#include "OrbitalEngine/Services/PhysicsEngineInterface.h"
#include "OrbitalEngine/OrbitalApplication.h"

namespace Orbital
{
	PhysicsEngineInterface::PhysicsEngineInterface()
		: ServiceInterface()
	{
	}

	PhysicsEngineInterface::PhysicsEngineInterface(const SharedApplication& app)
		: ServiceInterface(app)
	{
	}

	void PhysicsEngineInterface::Initialize()
	{
		mInstance = mApp.lock()->getPhysicsEngine();
	}

	void PhysicsEngineInterface::ClearComponents()
	{
		mInstance.lock()->clearColliders();
	}



} // namespace Orbital
