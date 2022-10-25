#pragma once

#include "OrbitalPhysics/Context.h"
#include "OrbitalPhysics/RigidBodyData.h"
#include "OrbitalPhysics/Tools.h"
""

namespace Orbital
{
	class OPHYSICS_API PhysicsEngine
	{
	public:
		PhysicsEngine(Servi)

		void update(const Time& dt, RigidBodyData& data);

		float getQuadMomentsOfIntertia(float mass, float width, float height);
		std::vector<Physics::CollisionPoints> resolveCollisions();

	private:
		void applyGravity(const Time& dt, RigidBodyData& data);
	};
} // namespace Orbital
