#include "OrbitalScripts/CoreEditorApplication.h"
#include "OrbitalEngine/Components.h"
#include "OrbitalTools/Random.h"

namespace Orbital
{
	CoreEditorApplication::CoreEditorApplication(const Entity& baseEntity, const SharedApplication& app)
		: NativeScript(baseEntity, app)
	{
	}

	void CoreEditorApplication::onLoad()
	{
		size_t entityCountW = 10;
		float xIncrement = 2.0f / (float)entityCountW;
		float yIncrement = 2.0f / (float)entityCountW;
		float scale = xIncrement * 0.4f;
		float xOffset = -0.9f;
		float yOffset = -0.9f;

		for (size_t i = 0; i < entityCountW; i++)
		{
			for (size_t j = 0; j < entityCountW; j++)
			{
				auto e = ECS.CreateEntity();
				auto manager = e.get<NativeScriptManager>();
				auto t = e.push<TransformComponent>();

				float xPos = xOffset + i * xIncrement;
				float yPos = yOffset + j * yIncrement;

				t->position.x = xPos;
				t->position.y = yPos;
				t->scale *= scale;

				MeshType meshType;
				auto dynamics = e.push<DynamicsComponent>(t);
				dynamics->mass = 5.0f;

				if (i == 0 and j == 0)
				{
					manager->push("PlayerController", e);
					meshType = MeshType::Sphere;
					dynamics->gravity = false;
					dynamics->mass = 10.0f;
				}
				else
				{
					meshType = MeshType::Sphere;
				}

				auto sphere = e.push<SphereCollider>(t, dynamics);
				auto sphere2 = e.get<SphereCollider>();
				dynamics->gravity = false;
				sphere->setRadius(scale / 2);

				auto m = Renderer.PushMeshComponent(e, meshType, t);
			}
		}

		// auto e = mServices.ECS.CreateEntity();
		// auto t = e.push<TransformComponent>();
		// t->position.x = 0.0;
		// t->position.y = -0.9f;
		// t->scale = { 1.0f, -0.01f, 0.0f };

		// auto dynamics = e.push<DynamicsComponent>(t);
		// dynamics->mass = 1000.0f;
		// auto plane = e.push<PlaneCollider>(t, dynamics);
		// dynamics->gravity = false;

		// plane->setNormal({0.0f, 1.0f, 0.0f});
		// auto m = mServices.Renderer.PushMeshComponent(e, MeshType::Quad, t);

		Physics.SetCollisionSolver(
			[](Collision collision, const Time& dt)
			{
				auto dynamicsA = collision.A.get<DynamicsComponent>();
				auto dynamicsB = collision.B.get<DynamicsComponent>();

				auto colliderA = collision.A.get<Collider>();
				auto colliderB = collision.B.get<Collider>();

				auto velocityDifference = dynamicsA->velocity - dynamicsB->velocity;
				auto relativeSpeed = Maths::Dot(velocityDifference, collision.points.normal);

				if (relativeSpeed < 0.0f) // Smashing
				{
					float e = 0.5f;
					float num = -(1 + e) * relativeSpeed;
					float j = num / (Maths::Dot(collision.points.normal, collision.points.normal));
					j /= (1 / dynamicsA->mass + 1 / dynamicsB->mass);

					if (dynamicsA.isValid())
					{
						dynamicsA->velocity += j / dynamicsA->mass * collision.points.normal;
					}

					if (dynamicsB.isValid())
					{
						dynamicsB->velocity -= j / dynamicsB->mass * collision.points.normal;
					}

					if (colliderA->isTrigger())
						colliderA->trigger();

					if (colliderB->isTrigger())
						colliderB->trigger();
				}
			}
		);
		Logger::Trace("Done loading CoreEditorApplication");
	}

	void CoreEditorApplication::onStart()
	{
	}

	void CoreEditorApplication::onUpdate(const Time& dt)
	{
	}

	OE_DEFINE_CREATOR(CoreEditorApplication);
} // namespace Orbital
