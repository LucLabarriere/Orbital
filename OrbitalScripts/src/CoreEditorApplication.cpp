#include "OrbitalScripts/CoreEditorApplication.h"
#include "OrbitalEngine/ECS/Components.h"
#include "OrbitalPhysics/Colliders.h"
#include "OrbitalScripts/PlayerController.h"
#include "OrbitalTools/Random.h"

namespace Orbital
{
	CoreEditorApplication::CoreEditorApplication(const Entity& baseEntity) : NativeScript(baseEntity)
	{
	}

	void CoreEditorApplication::onLoad()
	{
		auto e = ECS.CreateEntity();
		auto t = e.push<TransformComponent>();
		t->scale *= 0.1f;

		auto physics = e.push<PhysicsComponent>(Physics::ColliderType::Sphere);
		auto& collider = physics->getCastedCollider<Physics::SphereCollider>();
		auto playerController = e.push<PlayerController>();
		playerController->setSpeed(2.0f);

		auto filter = e.push<MeshFilter>(MeshType::Sphere);
		MeshComponent& m = e.push<MeshComponent>().get();

		collider.setCollisionCallback(
			[&collider, &m](Physics::Collider& other) {
				m.setColor({ 0.1f, 0.2f, 1.0f, 1.0f });
			}
		);

		Logger::Trace("Done loading CoreEditorApplication");
	}

	void CoreEditorApplication::onStart()
	{
	}

	void CoreEditorApplication::onPreUpdate(const Time& dt)
	{
	}

	OE_DEFINE_CREATOR(CoreEditorApplication);

} // namespace Orbital
