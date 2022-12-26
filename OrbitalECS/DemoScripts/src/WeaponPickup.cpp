#include "DemoScripts/WeaponPickup.h"

#include "DemoScripts/PlayerController.h"

#include "OrbitalPhysics/Colliders/SphereCollider.h"

namespace Demo
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
		auto filter = push<MeshFilter>(MeshType::Quad);
		auto mesh = push<MeshComponent>();
		auto physics = push<PhysicsComponent>(Physics::ColliderType::Sphere);
		get<TransformComponent>()->scale *= 0.05f;

		auto& collider = physics->getCastedCollider<Physics::SphereCollider>();
		collider.setCollisionCallback(
			[this](Physics::Collider& self, Physics::Collider& other)
			{
				auto otherEntity = ECS.GetEntity(other.getID());
				auto player = otherEntity.get<PlayerController>();

				if (player.isValid())
				{
					player->damage += 0.05f;
					player->cooldown -= player->cooldown * 0.1f;

					ECS.RequestDeleteEntity(mEntityID);
				}
			}
		);
	}

	void WeaponPickup::onPreUpdate(const Time& dt)
	{
	}

	void WeaponPickup::onUpdate(const Time& dt)
	{
	}
} // namespace Demo

OE_DEFINE_CREATOR(Demo, WeaponPickup);
