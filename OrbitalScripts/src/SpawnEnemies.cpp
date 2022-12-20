#include "OrbitalScripts/SpawnEnemies.h"
#include "OrbitalEngine/ECS/Components.h"
#include "OrbitalScripts/EnemyScript.h"
#include "OrbitalScripts/WeaponPickup.h"
#include "OrbitalTools/Random.h"

SpawnEnemies::SpawnEnemies(const Entity& baseEntity) : NativeScript(baseEntity)
{
}

void SpawnEnemies::onLoad()
{
}

void SpawnEnemies::onStart()
{
}

void SpawnEnemies::onCreate()
{
	mChrono.reset();
	mPickupChrono.reset();
}

void SpawnEnemies::onPreUpdate(const Time& dt)
{
}

void SpawnEnemies::onUpdate(const Time& dt)
{
	if (mChrono.measure().seconds() > mCoolDown)
	{
		auto e = ECS.CreateEntity();

		float random_x = (Random::Get() * 0.95f) * 2.0f - 1.0f;
		float random_y = (Random::Get() * 0.85f) * 2.0f - 1.0f;
		auto t = e.push<TransformComponent>();
		t->position.x = random_x;
		t->position.y = random_y;

		auto script = e.push<EnemyScript>();
		script->setPlayer(mPlayer.getEntityID());

		mChrono.reset();
	}

	if (mPickupChrono.measure().seconds() > mPickUpCooldown)
	{
		float random_x = (Random::Get() * 0.95f) * 2.0f - 1.0f;
		float random_y = (Random::Get() * 0.85f) * 2.0f - 1.0f;

		auto e = ECS.CreateEntity();
		auto script = e.push<WeaponPickup>();

		mPickupChrono.reset();
	}
}

OE_DEFINE_CREATOR(SpawnEnemies);
