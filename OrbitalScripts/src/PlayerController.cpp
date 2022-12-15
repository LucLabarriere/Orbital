#include "OrbitalScripts/PlayerController.h"
#include "OrbitalEngine/ECS/Components.h"
#include "OrbitalEngine/ECS/Components/NativeScript.h"
#include "OrbitalPhysics/Colliders.h"
#include "OrbitalScripts/EnemyScript.h"
#include "OrbitalScripts/ProjectileScript.h"

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
		auto physics = push<PhysicsComponent>(Physics::ColliderType::Sphere);
		auto& collider = physics->getCastedCollider<Physics::SphereCollider>();

		auto filter = push<MeshFilter>(MeshType::Sphere);
		MeshComponent& m = push<MeshComponent>().get();

		collider.setCollisionCallback(
			[this](Physics::Collider& self, Physics::Collider& other)
			{
				auto& meshComponent = *get<MeshComponent>();
				auto otherEntity = ECS.GetEntity(other.getID());

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
		mCooldown = 0.2f;
		mMaxHealth = 5;
		mHealth = mMaxHealth;
	}

	void PlayerController::onPreUpdate(const Time& dt)
	{
		float color = (float)mHealth / (float)mMaxHealth;
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
			if (mChrono.measure().seconds() > mCooldown)
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
			mHealth -= 1;
			mRecoveryChrono.reset();
		}

		if (mHealth <= 0)
			Logger::Debug("Game over");
	}

	void PlayerController::spawnProjectile()
	{
		auto position = get<TransformComponent>()->position;

		Maths::Vec2 target = Inputs::GetScreenSpaceMousePosition();

		Maths::Vec3 direction = Maths::Vec3{ target.x, target.y, 0.0f } - position;
		direction = Maths::Normalize(direction);

		auto projectile = ECS.CreateEntity();
		projectile.push<MeshFilter>(MeshType::Sphere);
		projectile.push<MeshComponent>();
		auto& physics = *projectile.push<PhysicsComponent>(Physics::ColliderType::Sphere);
		auto& collider = physics.getCastedCollider<Physics::SphereCollider>();

		projectile.get<TransformComponent>()->position = position;

		auto script = projectile.push<ProjectileScript>();
		script->direction = direction;

		collider.setCollisionCallback(
			[this](Physics::Collider& self, Physics::Collider& other)
			{
				Entity otherEntity = ECS.GetEntity(other.getID());
				auto enemy = otherEntity.get<EnemyScript>();

				if (enemy.isValid())
				{
					enemy->getHit();
					auto projectile = ECS.GetEntity(self.getID());
					ECS.RequestDeleteEntity(projectile.getEntityID());
				}
			}
		);
	}

	OE_DEFINE_CREATOR(PlayerController);
} // namespace Orbital
