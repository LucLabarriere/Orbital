#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/Components/Colliders.h"
#include "OrbitalEngine/Components/TransformComponent.h"
#include "OrbitalEngine/Services.h"
#include "OrbitalEngine/Services/ECSInterface.h"

namespace Orbital
{
	using PhysicsEngineServices = Services<AccessECS>;

	class PhysicsEngine : public Services<AccessECS>
	{
	public:
		PhysicsEngine(const SharedApplication& app);

		void initialize();
		void terminate();

		void onUpdate(const Time& dt);

		static CollisionPoints GetPlanePlaneCollisionPoints(const PlaneCollider& c1, const PlaneCollider& c2);
		static CollisionPoints GetPlaneSphereCollisionPoints(const PlaneCollider& c1, const SphereCollider& c2);
		static CollisionPoints GetSphereSphereCollisionPoints(const SphereCollider& c1, const SphereCollider& c2);

	private:
		friend class PhysicsInterface;

		std::function<void(Collision, const Time&)> mCollisionSolver = [](Collision collision, const Time& dt) {};
	};

} // namespace Orbital
