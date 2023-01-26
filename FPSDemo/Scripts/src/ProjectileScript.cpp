#include "FPSDemoScripts/ProjectileScript.h"

#include "FPSDemoLibrary/Components.h"
#include "FPSDemoScripts/EnemyScript.h"

#include "OrbitalPhysics/Colliders/SphereCollider.h"

namespace FPSDemo
{
	ProjectileScript::ProjectileScript(const Entity& baseEntity) : NativeScript(baseEntity)
	{
	}

	void ProjectileScript::onLoad()
	{
	}

	void ProjectileScript::onStart()
	{
	}

	void ProjectileScript::onCreate()
	{
		push<MeshFilter>(MeshType::Sphere);
		push<MeshComponent>();

		auto& physics = *get<PhysicsComponent>();
		auto& collider = physics.getCastedCollider<Physics::SphereCollider>();

		collider.setCollisionCallback(
			[this](Physics::Collider& self, Physics::Collider& other)
			{
				Entity otherEntity = ECS.GetEntity(other.getID());
				auto enemy = otherEntity.get<EnemyScript>();

				if (enemy.isValid())
				{
					auto& otherHealth = *otherEntity.get<Health>();
					otherHealth.getHit(this->damage);
					ECS.RequestDeleteEntity(mEntityID);
				}
			}
		);

		get<TransformComponent>()->scale *= 0.02f;
		mChrono.reset();
	}

	void ProjectileScript::onPreUpdate(const Time& dt)
	{
	}

	void ProjectileScript::onUpdate(const Time& dt)
	{
		if (mChrono.measure().seconds() > lifetime)
		{
			ECS.RequestDeleteEntity(mEntityID);
			return;
		}

		get<TransformComponent>()->position += this->direction * this->speed * dt.seconds();
	}
} // namespace FPSDemo

OE_DEFINE_CREATOR(FPSDemo, ProjectileScript)
