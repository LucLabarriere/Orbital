#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/Components/ColliderComponent.h"
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

		void SetCollision2DSolver(const std::function<void(Collision2D, const Time& dt)> callback);
		void SetCollision3DSolver(const std::function<void(Collision3D, const Time& dt)> callback);

		void ResetCollisionSolvers();
		void SetVerletSteps(size_t value);
		size_t GetVerletSteps() const;

	private:
		PhysicsEngine* mInstance = nullptr;
	};

	OCREATE_SERVICE(Physics);

} // namespace Orbital
