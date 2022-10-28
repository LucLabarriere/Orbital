#pragma once

#include "OrbitalECS/ECS.h"
#include "OrbitalEngine/Physics/Collider.h"
#include "OrbitalEngine/Services/ServiceInterface.h"
#include "OrbitalTools/Time.h"

namespace Orbital
{
	class PhysicsEngine;

	class OENGINE_API PhysicsInterface : public ServiceInterface
	{
	public:
		PhysicsInterface(const SharedApplication& app);
		void Initialize();

		void OnUpdate(const Time& dt);
		void SetCollisionSolver(const std::function<void(Collision, const Time& dt)> callback);
		void ResetCollisionSolver();

	private:
		PhysicsEngine* mInstance = nullptr;
	};
} // namespace Orbital
