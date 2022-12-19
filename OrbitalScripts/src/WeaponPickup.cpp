#include "OrbitalScripts/WeaponPickup.h"
#include "OrbitalEngine/ECS/Components.h"
#include "OrbitalTools/Random.h"

namespace Orbital
{
	WeaponPickup::WeaponPickup(const Entity& baseEntity) : NativeScript(baseEntity)
	{
	}

	void WeaponPickup::onLoad()
	{
	}

	void WeaponPickup::onStart()
	{
	}

	void WeaponPickup::onCreate()
	{
		float random_x = (Random::Get() * 0.95f) * 2.0f - 1.0f;
		float random_y = (Random::Get() * 0.85f) * 2.0f - 1.0f;
		auto t = push<TransformComponent>();
		t->position.x = random_x;
		t->position.y = random_y;
		t->scale *= 0.05f;
		auto filter = push<MeshFilter>(MeshType::Quad);
		auto mesh = push<MeshComponent>();
		auto physics = push<PhysicsComponent>(Physics::ColliderType::Sphere);
	}

	void WeaponPickup::onPreUpdate(const Time& dt)
	{
	}

	void WeaponPickup::onUpdate(const Time& dt)
	{
	}

	OE_DEFINE_CREATOR(WeaponPickup);

} // namespace Orbital
