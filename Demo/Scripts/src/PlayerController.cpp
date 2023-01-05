#include "DemoScripts/PlayerController.h"

#include "DemoLibrary/Components.h"
#include "DemoScripts/EnemyScript.h"
#include "DemoScripts/ProjectileScript.h"
#include "DemoScripts/WeaponPickup.h"

#include "OrbitalPhysics/Colliders.h"

namespace Demo
{
	PlayerController::PlayerController(const Entity& e) : NativeScript(e), fireChrono(0.5f), recoveryChrono(0.5f)
	{
	}

	void PlayerController::onLoad()
	{
	}

	void PlayerController::onCreate()
	{
		mTransform = push<TransformComponent>();
		mTransform->position = { 0.0f, 0.0f, 0.0f };
		mTransform->scale *= 0.1f;

		auto health = push<Health>();
		health->deathCallback = [this]() { Scenes.Reload(); };

		auto physics = push<PhysicsComponent>(Physics::ColliderType::Sphere);
		auto& collider = physics->getCastedCollider<Physics::SphereCollider>();

		auto filter = push<MeshFilter>(MeshType::Cube);
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

		fireChrono.reset();
		recoveryChrono.reset();

		this->speed = 0.6f;
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
		TransformComponent& transform = *get<TransformComponent>();

		if (Inputs::IsKeyDown(OE_KEY_S)) // Backward
		{
			transform.position.y -= this->speed * dt.seconds();
		}

		if (Inputs::IsKeyDown(OE_KEY_W)) // Forward
		{
			transform.position.y += this->speed * dt.seconds();
		}

		if (Inputs::IsKeyDown(OE_KEY_A)) // Left
		{
			transform.position.x -= this->speed * dt.seconds();
		}

		if (Inputs::IsKeyDown(OE_KEY_D)) // Right
		{
			transform.position.x += this->speed * dt.seconds();
		}

		if (Inputs::IsKeyDown(OE_KEY_ENTER) || Inputs::IsMouseButtonDown(OE_MOUSE_BUTTON_LEFT))
		{
			if (fireChrono.ready())
			{
				spawnProjectile();
			}
		}

		auto& p1 = this->camera.get<TransformComponent>()->position;
		auto& p2 = transform.position;
		auto& r1 = this->camera.get<TransformComponent>()->rotation;
		//p1 = Maths::Vec3{ p2.x, p2.y, - 3.0f };
		p1 = Maths::Vec3{ 0.0f, 0.0f, - 3.0f };

		this->camera.get<CameraComponent>()->lookAt(Maths::Vec3(0.0f));
	}

	void PlayerController::getHit()
	{
		if (recoveryChrono.ready())
		{
			get<Health>()->getHit(10.0f);
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
} // namespace Demo

OE_DEFINE_CREATOR(Demo, PlayerController);
