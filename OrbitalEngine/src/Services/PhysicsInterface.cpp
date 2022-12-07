#include "OrbitalEngine/Services/PhysicsInterface.h"
#include "OrbitalEngine/OrbitalApplication.h"

namespace Orbital
{
	PhysicsInterface::PhysicsInterface()
		: ServiceInterface()
	{
	}

	PhysicsInterface::PhysicsInterface(const SharedApplication& app)
		: ServiceInterface(app)
	{
	}

	void PhysicsInterface::Initialize()
	{
		mInstance = mApp.lock()->getPhysicsEngine();
	}




} // namespace Orbital
