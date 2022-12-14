#include "OrbitalScripts/SpawnEnemies.h"
#include "OrbitalScripts/EnemyScript.h"
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
			t->scale *= 0.1f;
			t->position.x = random_x;
			t->position.y = random_y;
			auto filter = e.push<MeshFilter>(MeshType::Sphere);
			auto mesh = e.push<MeshComponent>();
			auto physics = e.push<PhysicsComponent>(Physics::ColliderType::Sphere);
			auto script = e.push<EnemyScript>();
			script->setPlayer(mPlayer.getEntityID());
			mesh->setColor({1.0f, 0.0f, 0.0f, 1.0f});

			mChrono.reset();
		}
	}

	OE_DEFINE_CREATOR(SpawnEnemies);

} // namespace Orbital
