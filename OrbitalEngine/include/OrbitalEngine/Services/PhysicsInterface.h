#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/Physics/Collider.h"
#include "OrbitalEngine/Services.h"
#include "OrbitalEngine/Services/ServiceInterface.h"

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

	OCREATE_SERVICE(Physics);

} // namespace Orbital
