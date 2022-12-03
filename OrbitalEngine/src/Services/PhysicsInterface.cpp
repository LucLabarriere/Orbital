#include "OrbitalEngine/Services/PhysicsInterface.h"
#include "OrbitalEngine/OrbitalApplication.h"

namespace Orbital
{
	PhysicsInterface::PhysicsInterface(const SharedApplication& app)
		: ServiceInterface(app)
	{
	}

	void PhysicsInterface::Initialize()
	{
		mInstance = mApp->getPhysicsEngine();
	}




} // namespace Orbital
