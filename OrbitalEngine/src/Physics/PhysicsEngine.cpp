#include "OrbitalEngine/Physics/PhysicsEngine.h"

namespace Orbital
{
	PhysicsEngine::PhysicsEngine(const SharedApplication& app) : PhysicsEngineServices(app)
	{
		LOGFUNC();
	}

	void PhysicsEngine::initialize()
	{
		LOGFUNC();
	}

	void PhysicsEngine::terminate()
	{
		LOGFUNC();
	}

	void PhysicsEngine::onUpdate(const Time& dt)
	{
		auto& colliders = ECS.DerivedComponents<Collider>();

		std::vector<Collision> collisions;
		collisions.reserve(colliders.size());

		for (auto& [id1, c1] : colliders)
		{
			for (auto& [id2, c2] : colliders)
			{
				if (id1 == id2)
					break;

				CollisionPoints points = c1->getCollisionPoints(*c2);

				if (points.collide)
				{
					collisions.push_back({ ECS.GetEntity(id1), ECS.GetEntity(id2), points });
				}
			}
		}

		for (auto& collision : collisions)
		{
			mCollisionSolver(collision, dt);
		}

		for (auto& [id, dynamics] : ECS.Components<DynamicsComponent>())
		{

			// Euler integration
			if (dynamics.gravity)
				dynamics.force += Maths::Vec3({ 0.0f, -9.81f, 0.0f });

			dynamics.velocity += dynamics.force / dynamics.mass * dt.seconds();
			// dynamics.velocity -= dynamics.velocity * 0.02f; // Slow down
			dynamics.transform->position += dynamics.velocity * dt.seconds();

			dynamics.force = { 0.0f, 0.0f, 0.0f };
		}
	}

	CollisionPoints PhysicsEngine::GetPlanePlaneCollisionPoints(const PlaneCollider& p1, const PlaneCollider& p2)
	{
		return {};
	}
	CollisionPoints PhysicsEngine::GetPlaneSphereCollisionPoints(const PlaneCollider& p, const SphereCollider& s)
	{
		Maths::Vec3 diffVector = s.getTransform()->position - p.getTransform()->position;
		float projection = Maths::Dot(diffVector, p.getNormal());
		float distance = Maths::Absolute(projection);

		return {
			.A = p.getTransform()->position,
			.B = s.getTransform()->position,
			.vector = p.getNormal() * distance,
			.normal = p.getNormal(),
			.distance = distance,
			.collide = (projection < s.getRadius() ? true : false),
		};
	}
	CollisionPoints PhysicsEngine::GetSphereSphereCollisionPoints(const SphereCollider& s1, const SphereCollider& s2)
	{
		Maths::Vec3 vector = s2.getTransform()->position - s1.getTransform()->position;
		float distance = Maths::Norm(vector);
		Maths::Vec3 normal = vector / distance;

		return {
			.A = s1.getTransform()->position,
			.B = s2.getTransform()->position,
			.vector = vector,
			.normal = normal,
			.distance = distance,
			.collide = (distance < s1.getRadius() + s2.getRadius() ? true : false),
		};
	}
} // namespace Orbital
