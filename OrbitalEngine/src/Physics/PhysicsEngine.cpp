#include "OrbitalEngine/Physics/PhysicsEngine.h"
#include "OrbitalEngine/Components/Physics2D/RigidBody2D.h"
#include "OrbitalEngine/Components/Physics3D/RigidBody3D.h"

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

	void PhysicsEngine::onUpdate2D(const Time& dt)
	{
		auto& colliders = ECS.DerivedComponents<Collider2DComponent>();

		std::vector<Collision2D> collisions;
		collisions.reserve(colliders.size());

		for (auto& [id1, c1] : colliders)
		{
			for (auto& [id2, c2] : colliders)
			{
				if (id1 == id2)
					break;

				Collision2DPoints points = c1->getCollisionPoints(*c2);

				if (points.collide)
				{
					collisions.push_back({ ECS.GetEntity(id1), ECS.GetEntity(id2), points });
				}
			}
		}

		for (auto& collision : collisions)
			mCollision2DSolver(collision, dt);
	}

	void PhysicsEngine::onUpdate3D(const Time& dt)
	{
		auto& colliders = ECS.DerivedComponents<Collider3DComponent>();

		std::vector<Collision3D> collisions;
		collisions.reserve(colliders.size());

		for (auto& [id1, c1] : colliders)
		{
			for (auto& [id2, c2] : colliders)
			{
				if (id1 == id2)
					break;

				Collision3DPoints points = c1->getCollisionPoints(*c2);

				if (points.collide)
				{
					collisions.push_back({ ECS.GetEntity(id1), ECS.GetEntity(id2), points });
				}
			}
		}

		for (auto& collision : collisions)
			mCollision3DSolver(collision, dt);
	}

	template <typename T>
	void PhysicsEngine::verletIntegration(const Time& dt, std::unordered_map<EntityID, T>& bodies)
	{
		for (auto& [id, dynamics] : bodies)
		{
			float timeIncrement = dt.seconds() / mVerletSteps;

			for (size_t i = 0; i < mVerletSteps; i++)
			{
				if (dynamics.gravity)
					dynamics.force += T::GravityForce();

				auto acceleration = dynamics.force / dynamics.mass;

				auto positionChange = dynamics.velocity * timeIncrement + 1.0f / 2.0f * acceleration * timeIncrement;

				dynamics.transform->position.x += positionChange.x;
				dynamics.transform->position.y += positionChange.y;

				if constexpr (std::is_base_of<RigidBody3D, T>::value)
				{
					dynamics.transform->position.z += positionChange.z;
				}

				dynamics.force = T::NullForce();
			}
		}
	}

	template void PhysicsEngine::verletIntegration<RigidBody2D>(
		const Time& dt, std::unordered_map<EntityID, RigidBody2D>& bodies
	);

	template void PhysicsEngine::verletIntegration<RigidBody3D>(
		const Time& dt, std::unordered_map<EntityID, RigidBody3D>& bodies
	);
} // namespace Orbital
