#include "FPSDemoScripts/CoreScript.h"

#include "FPSDemoScripts/EnemyScript.h"
#include "FPSDemoScripts/PlayerController.h"
#include "FPSDemoScripts/WeaponPickup.h"
#include "OrbitalScripts/FPSCameraController.h"

namespace FPSDemo
{
	CoreScript::CoreScript(const Entity& baseEntity) : NativeScript(baseEntity)
	{
	}

	void CoreScript::onLoad()
	{
		{
			auto floor = ECS.CreateEntity();
			auto& transform = *floor.push<TransformComponent>();
			transform.scale.y = 0.01f;
			transform.scale.x = 3.0f;
			transform.scale.z = 3.0f;
			floor.push<MeshFilter>(MeshType::Quad);
			floor.push<MeshComponent>();
		}

		{
			auto wall = ECS.CreateEntity();
			auto& transform = *wall.push<TransformComponent>();
			transform.scale.x = 2.0f;
			transform.scale.y = 2.0f;
			transform.scale.z = 0.01f;
			transform.position = Maths::Vec3{ 0.0f, 0.5f, 2.0f};
			wall.push<MeshFilter>(MeshType::Quad);
			wall.push<MeshComponent>()->setColor({0.3f, 0.7f, 0.6f, 1.0f});
		}

		{
			auto wall = ECS.CreateEntity();
			auto& transform = *wall.push<TransformComponent>();
			transform.scale.x = 2.0f;
			transform.scale.y = 2.0f;
			transform.scale.z = 0.01f;
			transform.position = Maths::Vec3{ 0.0f, 0.5f, -2.0f};
			wall.push<MeshFilter>(MeshType::Quad);
			wall.push<MeshComponent>()->setColor({0.0f, 0.1f, 0.3f, 1.0f});
		}

		{
			auto wall = ECS.CreateEntity();
			auto& transform = *wall.push<TransformComponent>();
			transform.scale.x = 3.0f;
			transform.scale.y = 0.01f;
			transform.scale.z = 3.0f;
			transform.position = Maths::Vec3{ 0.0f, 2.5f, 0.0f}; wall.push<MeshFilter>(MeshType::Quad);
			wall.push<MeshComponent>()->setColor({0.0f, 0.3f, 0.1f, 1.0f});
		}

		camera = ECS.CreateEntity();
		auto cameraComponent = camera.push<CameraComponent>(CameraSpecs{
			.behavior = CameraBehavior::Type::Free,
			.projection = CameraProjection::Type::Perspective,
		});
		camera.push<FPSCameraController>();
		Scenes.SetMainCamera(camera);

		player = ECS.CreateEntity();
		auto& playerScript = *player.push<PlayerController>();

		enemyEvent.chrono.reset();
		pickupEvent.chrono.reset();
		enemyEvent.cd = 3.0f;
		pickupEvent.cd = 1.0f;
	}

	void CoreScript::onUpdate(const Time& dt)
	{
	}
} // namespace FPSDemo

OE_DEFINE_CREATOR(FPSDemo, CoreScript)
