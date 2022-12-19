#include "OrbitalScripts/PlayerController.h"
#include "OrbitalEngine/ECS/Components.h"
#include "OrbitalEngine/ECS/Components/NativeScript.h"
#include "OrbitalPhysics/Colliders.h"
#include "OrbitalScripts/EnemyScript.h"
#include "OrbitalScripts/WeaponPickup.h"
#include "OrbitalScripts/ProjectileScript.h"
#include "OrbitalScripts/Components/Components.h"

namespace Orbital
{
	PlayerController::PlayerController(const Entity& e) : NativeScript(e)
	{
	}

	void PlayerController::onLoad()
	{
	}

	void PlayerController::onCreate()
	{
		mTransform = push<TransformComponent>();
		mTransform->scale *= 0.1f;
		auto health = push<Health>();
		health->deathCallback = [](){
			Logger::Debug("Game Over");
		};

		auto physics = push<PhysicsComponent>(Physics::ColliderType::Sphere);
		auto& collider = physics->getCastedCollider<Physics::SphereCollider>();

		auto filter = push<MeshFilter>(MeshType::Sphere);
		MeshComponent& m = push<MeshComponent>().get();

		collider.setCollisionCallback(
			[this](Physics::Collider& self, Physics::Collider& other)
			{
				auto& meshComponent = *get<MeshComponent>();
				auto otherEntity = ECS.GetEntity(other.getID());
				auto pickup = otherEntity.get<WeaponPickup>();

				if (otherEntity.get<EnemyScript>().isValid())
				{
					meshComponent.setColor({ 1.0f, 1.0f, 1.0f, 1.0f });
					getHit();
				}
			}
		);

		mChrono.reset();
		mRecoveryTime = 0.5f;
		mSpeed = 0.6f;
		this->cooldown = 0.5f;
		this->damage = 0.4f;
	}

	void PlayerController::onPreUpdate(const Time& dt)
	{
		auto& health = *get<Health>();
		float color = health.current / health.max;
		get<MeshComponent>()->setColor({ 1.0f - color, color, 0.0f, 1.0f });
	}

	void PlayerController::onUpdate(const Time& dt)
	{
		TransformComponent& tempTransform = *mTransform;

		if (Inputs::IsKeyDown(OE_KEY_Q))
		{
			tempTransform.scale -= Maths::Absolute(mSpeed * 0.1f * dt.seconds());
		}

		if (Inputs::IsKeyDown(OE_KEY_E))
		{
			tempTransform.scale += Maths::Absolute(mSpeed * 0.1f * dt.seconds());
		}

		if (Inputs::IsKeyDown(OE_KEY_S))
		{
			// dynamics->velocity.y -= mSpeed * dt.seconds();
			tempTransform.position.y -= mSpeed * dt.seconds();
		}

		if (Inputs::IsKeyDown(OE_KEY_W))
		{
			// dynamics->velocity.y += mSpeed * dt.seconds();
			tempTransform.position.y += mSpeed * dt.seconds();
		}

		if (Inputs::IsKeyDown(OE_KEY_A))
		{
			// dynamics->velocity.x -= mSpeed * dt.seconds();
			tempTransform.position.x -= mSpeed * dt.seconds();
		}

		if (Inputs::IsKeyDown(OE_KEY_D))
		{
			// dynamics->velocity.x += mSpeed * dt.seconds();
			tempTransform.position.x += mSpeed * dt.seconds();
		}

		if (Inputs::IsKeyDown(OE_KEY_ENTER) || Inputs::IsMouseButtonDown(OE_MOUSE_BUTTON_LEFT))
		{
			if (mChrono.measure().seconds() > this->cooldown)
			{
				spawnProjectile();
				mChrono.reset();
			}
		}
	}

	void PlayerController::getHit()
	{
		if (mRecoveryChrono.measure().seconds() > mRecoveryTime)
		{
			get<Health>()->getHit(10.0f);
			mRecoveryChrono.reset();
		}
	}

	void PlayerController::spawnProjectile()
	{
		auto position = get<TransformComponent>()->position;

		Maths::Vec2 target = Inputs::GetScreenSpaceMousePosition();

		Maths::Vec3 direction = Maths::Vec3{ target.x, target.y, 0.0f } - position;
		direction = Maths::Normalize(direction);

		auto projectile = ECS.CreateEntity();
		auto physics = projectile.push<PhysicsComponent>(Physics::ColliderType::Sphere);
		projectile.get<TransformComponent>()->position = position;
		auto script = projectile.push<ProjectileScript>();
		script->direction = direction;
		script->damage = this->damage;
	}

	OE_DEFINE_CREATOR(PlayerController);
} // namespace Orbital
