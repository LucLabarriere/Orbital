#include "OrbitalScripts/CoreDemoApplication.h"
#include "OrbitalEngine/ECS/Components.h"
#include "OrbitalTools/Random.h"

#include "OrbitalScripts/EnemyScript.h"
#include "OrbitalScripts/PlayerController.h"
#include "OrbitalScripts/WeaponPickup.h"

CoreDemoApplication::CoreDemoApplication(const Entity& baseEntity) : NativeScript(baseEntity)
{
}

void CoreDemoApplication::onLoad()
{
	player = ECS.CreateEntity();
	player.push<PlayerController>();

	enemyEvent.chrono.reset();
	pickupEvent.chrono.reset();
	enemyEvent.cd = 3.0;
	pickupEvent.cd = 5.0;
}

void CoreDemoApplication::onUpdate(const Time& dt)
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

OE_DEFINE_CREATOR(CoreDemoApplication);
