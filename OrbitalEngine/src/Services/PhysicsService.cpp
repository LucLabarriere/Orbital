#include "OrbitalEngine/Services/PhysicsService.h"
#include "OrbitalEngine/OrbitalApplication.h"
#include "OrbitalEngine/Physics/PhysicsEngine.h"

namespace Orbital
{
	PhysicsInterface::PhysicsInterface(const SharedApplication& app) : ServiceInterface(app)
	{
	}

	void PhysicsInterface::Initialize()
	{
		mInstance = mApp->getPhysicsEngine();
	}

	void PhysicsInterface::OnUpdate(const Time& dt)
	{
		mInstance->onUpdate(dt);
	}

	void PhysicsInterface::SetCollisionSolver(const std::function<void(Collision, const Time& dt)> callback)
	{
		mInstance->mCollisionSolver = callback;
	}

	void PhysicsInterface::ResetCollisionSolver()
	{
		mInstance->mCollisionSolver = [](Collision col, const Time& dt) {};
	}

} // namespace Orbital
