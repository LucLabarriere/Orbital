#include "OrbitalEngine/OrbitalApplication.h"
#include "OrbitalEngine/Physics/PhysicsEngine.h"
#include "OrbitalEngine/Services/PhysicsInterface.h"

namespace Orbital
{
	PhysicsInterface::PhysicsInterface(const SharedApplication& app) : ServiceInterface(app)
	{
	}

	void PhysicsInterface::Initialize()
	{
		//mInstance = mApp->getPhysicsEngine();
	}

	void PhysicsInterface::SetCollision2DSolver(const std::function<void(Collision2D, const Time& dt)> callback)
	{
		mInstance->mCollision2DSolver = callback;
	}

	void PhysicsInterface::SetCollision3DSolver(const std::function<void(Collision3D, const Time& dt)> callback)
	{
		mInstance->mCollision3DSolver = callback;
	}

	void PhysicsInterface::ResetCollisionSolvers()
	{
		mInstance->mCollision2DSolver = [](Collision2D col, const Time& dt) {};
		mInstance->mCollision3DSolver = [](Collision3D col, const Time& dt) {};
	}

	void PhysicsInterface::SetVerletSteps(size_t value)
	{
		mInstance->setVerletSteps(value);
	}

	size_t PhysicsInterface::GetVerletSteps() const
	{
		return mInstance->getVerletSteps();
	}

} // namespace Orbital
