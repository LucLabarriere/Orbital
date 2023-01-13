#include "DemoScripts/CoreScript.h"

#include "DemoScripts/EnemyScript.h"
#include "DemoScripts/PlayerController.h"
#include "DemoScripts/WeaponPickup.h"
#include "OrbitalScripts/FreeCameraController.h"

namespace Demo
{
	CoreScript::CoreScript(const Entity& baseEntity) : NativeScript(baseEntity)
	{
	}

	void CoreScript::onLoad()
	{
		camera = ECS.CreateEntity();
		auto cameraComponent = camera.push<CameraComponent>(CameraSpecs{
			.behavior = CameraBehavior::Type::Free,
			.projection = CameraProjection::Type::Perspective,
		});
		Scenes.SetMainCamera(camera);

		//auto debugCamera = ECS.CreateEntity();
		//auto debugCameraComponent = debugCamera.push<CameraComponent>(CameraSpecs{
		//	.behavior = CameraBehavior::Type::Free,
		//	.projection = CameraProjection::Type::Perspective,
		//});
		//debugCamera.push<FreeCameraController>();
		//debugCamera.get<TransformComponent>()->position = Maths::Vec3{0.0f, 0.0f, -1.0f};
		//Renderer.SetCamera(debugCameraComponent);

		player = ECS.CreateEntity();
		player.push<PlayerController>()->camera = camera;

		enemyEvent.chrono.reset();
		pickupEvent.chrono.reset();
		enemyEvent.cd = 3.0f;
		pickupEvent.cd = 1.0f;
	}

	void CoreScript::onUpdate(const Time& dt)
	{
		if (enemyEvent.chrono.measure().seconds() > enemyEvent.cd)
		{
			auto e = ECS.CreateEntity();

			float random_x = (Random::Get() * 0.95f) * 2.0f - 1.0f;
			float random_y = (Random::Get() * 0.85f) * 2.0f - 1.0f;

			auto script = e.push<EnemyScript>();
			auto& position = e.get<TransformComponent>()->position;
			position.x = random_x;
			position.y = random_y;
			position.z = 0.0f;

			script->setPlayer(this->player.getEntityID());

			enemyEvent.chrono.reset();
		}

		if (pickupEvent.chrono.measure().seconds() > pickupEvent.cd)
		{
			auto e = ECS.CreateEntity();

			float random_x = (Random::Get() * 0.95f) * 2.0f - 1.0f;
			float random_y = (Random::Get() * 0.85f) * 2.0f - 1.0f;

			auto script = e.push<WeaponPickup>();
			auto& position = e.get<TransformComponent>()->position;

			position.x = random_x;
			position.y = random_y;

			pickupEvent.chrono.reset();
		}
	}
} // namespace Demo

OE_DEFINE_CREATOR(Demo, CoreScript);
