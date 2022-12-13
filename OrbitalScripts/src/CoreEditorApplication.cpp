#include "OrbitalScripts/CoreEditorApplication.h"
#include "OrbitalEngine/ECS/Components.h"
#include "OrbitalPhysics/Colliders.h"
#include "OrbitalScripts/PlayerController.h"
#include "OrbitalTools/Random.h"

namespace Orbital
{
	CoreEditorApplication::CoreEditorApplication(const Entity& baseEntity)
		: NativeScript(baseEntity)
	{
	}

	void CoreEditorApplication::onLoad()
	{
		size_t entityCountW = 5;
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
				auto t = e.push<TransformComponent>();
				auto t2 = e.get<TransformComponent>();

				float xPos = xOffset + i * xIncrement;
				float yPos = yOffset + j * yIncrement;

				t->position.x = xPos;
				t->position.y = yPos;
				t->scale *= scale;

				auto physics = e.push<PhysicsComponent>(Physics::ColliderType::Sphere);
				auto collider = physics->getCastedCollider<Physics::SphereCollider>().lock();
				collider->setRadius(scale / 2);

				// auto t2 = e.get<TransformComponent>();

				// auto dynamics = e.push<RigidBody2D>(t);
				// dynamics->mass = 5.0f;

				if (i == 0 and j == 0)
				{
					e.push<PlayerController>();
					auto playerControlerHandle = e.get<PlayerController>();
					playerControlerHandle->setSpeed(2.0f);

					// dynamics->gravity = false;
					// dynamics->mass = 10.0f;
				}

				// auto sphere = e.push<QuadCollider2D>(t, dynamics);
				// dynamics->gravity = false;

				auto filter = e.push<MeshFilter>(MeshType::Sphere);
				MeshComponent& m = e.push<MeshComponent>().get();

				m.setColor({ 1.0f, 0.0f, 0.0f, 1.0f });

				if (i == 0 and j == 0)
				{
					collider->setCollisionCallback(
						[&](Ref<Physics::Collider>& other)
						{
							m.setColor({ 0.1f, 0.2f, 1.0f, 1.0f });
						}
					);
				}
			}
		}

		Logger::Trace("Done loading CoreEditorApplication");
	}

	void CoreEditorApplication::onStart()
	{
	}

	void CoreEditorApplication::onPreUpdate(const Time& dt)
	{
		for (auto& [id, meshComponent] : ECS.Components<MeshComponent>())
		{
			meshComponent.setColor({ 1.0f, 0.2f, 0.2f, 1.0f });
		}
	}

	OE_DEFINE_CREATOR(CoreEditorApplication);

} // namespace Orbital
