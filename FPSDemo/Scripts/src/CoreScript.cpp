#include "FPSDemoScripts/CoreScript.h"

#include "FPSDemoScripts/EnemyScript.h"
#include "FPSDemoScripts/PlayerController.h"
#include "FPSDemoScripts/WeaponPickup.h"

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
			wall.push<MeshComponent>()->setColor({0.3f, 0.1f, 0.0f, 1.0f});
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

		player = ECS.CreateEntity();
		auto& playerScript = *player.push<PlayerController>();

		enemyEvent.chrono.reset();
		pickupEvent.chrono.reset();
		enemyEvent.cd = 3.0f;
		pickupEvent.cd = 1.0f;
	}

	void CoreScript::onUpdate(const Time& dt)
	{
		//if (enemyEvent.chrono.measure().seconds() > enemyEvent.cd)
		//{
		//	auto e = ECS.CreateEntity();

		//	float random_x = (Random::Get() * 0.95f) * 2.0f - 1.0f;
		//	float random_y = (Random::Get() * 0.85f) * 2.0f - 1.0f;

		//	auto script = e.push<EnemyScript>();
		//	auto& position = e.get<TransformComponent>()->position;
		//	position.x = random_x;
		//	position.y = random_y;

		//	script->setPlayer(this->player.getEntityID());

		//	enemyEvent.chrono.reset();
		//}

		//if (pickupEvent.chrono.measure().seconds() > pickupEvent.cd)
		//{
		//	auto e = ECS.CreateEntity();

		//	float random_x = (Random::Get() * 0.95f) * 2.0f - 1.0f;
		//	float random_y = (Random::Get() * 0.85f) * 2.0f - 1.0f;

		//	auto script = e.push<WeaponPickup>();
		//	auto& position = e.get<TransformComponent>()->position;

		//	position.x = random_x;
		//	position.y = random_y;

		//	pickupEvent.chrono.reset();
		//}
	}
} // namespace FPSDemo

OE_DEFINE_CREATOR(FPSDemo, CoreScript);
