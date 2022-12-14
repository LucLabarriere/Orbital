#include "OrbitalScripts/SpawnEnemies.h"
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
		mDt = Time(0);
	}

	void SpawnEnemies::onStart()
	{
	}

	void SpawnEnemies::onPreUpdate(const Time& dt)
	{
	}

	void SpawnEnemies::onUpdate(const Time& dt)
	{
		mDt += dt;

		if (mDt.seconds() > mCoolDown)
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
			mesh->setColor({1.0f, 0.0f, 0.0f, 1.0f});

			mDt = Time(0);
		}
	}

	OE_DEFINE_CREATOR(SpawnEnemies);

} // namespace Orbital
