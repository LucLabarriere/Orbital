#include "OrbitalScripts/CoreEditorApplication.h"
#include "OrbitalEngine/Components.h"
#include "OrbitalEngine/Components/Physics2D.h"
#include "OrbitalTools/Random.h"

namespace Orbital
{
	CoreEditorApplication::CoreEditorApplication(const Entity& baseEntity, const SharedApplication& app)
		: NativeScript(baseEntity, app)
	{
	}

	void CoreEditorApplication::onLoad()
	{
		size_t entityCountW = 1;
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

				//auto dynamics = e.push<RigidBody2D>(t);
				//dynamics->mass = 5.0f;

				if (i == 0 and j == 0)
				{
					manager->push("PlayerController", e);
					//dynamics->gravity = false;
					//dynamics->mass = 10.0f;
				}

				//auto sphere = e.push<QuadCollider2D>(t, dynamics);
				//dynamics->gravity = false;

				auto filter = e.push<MeshFilter>(MeshType::Quad);
				auto m = Renderer.PushMeshComponent(e, filter, t);
				m->setColor({ 1.0f, 0.0f, 0.0f, 1.0f });
			}
		}

		//Physics.SetCollision2DSolver(
		//	[](Collision2D collision, const Time& dt)
		//	{
		//		auto dynamicsA = collision.A.get<RigidBody2D>();
		//		auto dynamicsB = collision.B.get<RigidBody2D>();

		//		auto colliderA = collision.A.get<Collider2DComponent>();
		//		auto colliderB = collision.B.get<Collider2DComponent>();

		//		Maths::Vec2 velocityDifference = dynamicsA->velocity - dynamicsB->velocity;
		//		auto relativeSpeed = Maths::Dot(velocityDifference, collision.points.normal);

		//		if (relativeSpeed < 0.0f) // Smashing
		//		{
		//			float e = 0.5f;
		//			float num = -(1 + e) * relativeSpeed;
		//			float j = num / (Maths::Dot(collision.points.normal, collision.points.normal));
		//			j /= (1 / dynamicsA->mass + 1 / dynamicsB->mass);

		//			dynamicsA->velocity += j / dynamicsA->mass * collision.points.normal;
		//			dynamicsB->velocity -= j / dynamicsB->mass * collision.points.normal;
		//		}
		//	}
		//);
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
