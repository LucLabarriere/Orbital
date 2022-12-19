#include "OrbitalScripts/SpawnEnemies.h"
#include "OrbitalScripts/EnemyScript.h"
#include "OrbitalScripts/WeaponPickup.h"
#include "OrbitalEngine/ECS/Components.h"
#include "OrbitalTools/Random.h"

namespace Orbital
{
	SpawnEnemies::SpawnEnemies(const Entity& baseEntity)
		: NativeScript(baseEntity)
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
			float random_x = (Random::Get() * 0.95f) * 2.0f - 1.0f;
			float random_y = (Random::Get() * 0.85f) * 2.0f - 1.0f;
			auto e  = ECS.CreateEntity();
			auto t = e.push<TransformComponent>();
			t->position.x = random_x;
			t->position.y = random_y;
			auto filter = e.push<MeshFilter>(MeshType::Sphere);
			auto mesh = e.push<MeshComponent>();
			auto physics = e.push<PhysicsComponent>(Physics::ColliderType::Sphere);
			auto script = e.push<EnemyScript>();
			script->setPlayer(mPlayer.getEntityID());

			mChrono.reset();
		}

		if (mPickupChrono.measure().seconds() > mPickUpCooldown)
		{
			auto e  = ECS.CreateEntity();
			auto script = e.push<WeaponPickup>();

			script->damage = Random::Get() * 3.0f + 0.5f;
			script->firerate = Random::Get() * 0.3f + 0.02f;

			mPickupChrono.reset();
		}
	}

	OE_DEFINE_CREATOR(SpawnEnemies);

} // namespace Orbital
