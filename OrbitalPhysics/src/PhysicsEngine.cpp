#include "OrbitalPhysics/PhysicsEngine.h"

namespace Orbital
{

	void PhysicsEngine::Update(const Time& dt, RigidBodyData& data)
	{
		if (data.Gravity)
		{
			ApplyGravity(dt, data);
		}
	}

	float PhysicsEngine::GetQuadMomentsOfIntertia(float mass, float width, float height)
	{
		return (mass * ( width * width + height * height)) / 12;
	}

	Maths::Vec3 PhysicsEngine::GetTorque(const Maths::Vec3& com, const Maths::Vec3& offset)
	{;
		return Maths::Cross(offset, com);
	}

	std::vector<Physics::CollisionPoints> ResolveCollisions()
	{

	}

	void PhysicsEngine::ApplyGravity(const Time& dt, RigidBodyData& data)
	{
		Maths::Vec3 force = Maths::Vec3(0.0f, data.Mass * -9.81, 0.0f);
		Maths::Vec3 acceleration = force / data.Mass;
		data.Velocity += acceleration * dt.seconds();
		data.Position += data.Velocity * dt.seconds();
	}
} // namespace Orbital
