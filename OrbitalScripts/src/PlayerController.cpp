#include "OrbitalScripts/PlayerController.h"
#include "OrbitalEngine/ECS/Components.h"
#include "OrbitalEngine/ECS/Components/NativeScript.h"
#include "OrbitalPhysics/Colliders.h"
#include "OrbitalScripts/ProjectileScript.h"

namespace Orbital
{
	PlayerController::PlayerController(const Entity& e)
		: NativeScript(e), mSpeed(0.3f), mTransform(e.get<TransformComponent>())
	{
	}

	void PlayerController::onLoad()
	{
		mTransform->scale = Maths::Vec3(1.0f, 1.0f, 1.0f) * 0.1f;
	}

	void PlayerController::onPreUpdate(const Time& dt)
	{
		get<MeshComponent>()->setColor({ 0.0f, 1.2f, 0.2f, 1.0f });
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

		if (Inputs::IsKeyDown(OE_KEY_ENTER))
		{
			spawnProjectile();
		}
	}

	void PlayerController::spawnProjectile()
	{
		Maths::Vec2 target = Inputs::GetMousePosition();
		target.x /= 640.0f;
		target.y /= 480.0f;
		target = target * 2.0f - 1.0f;
		auto position = get<TransformComponent>()->position;

		Logger::Debug(target.x, " ", target.y);
		Maths::Vec3 direction = position - Maths::Vec3{ target.x, target.y, 0.0f };
		direction = Maths::Normalize(direction);
		direction.x = - direction.x;

		auto projectile = ECS.CreateEntity();
		projectile.push<MeshFilter>(MeshType::Sphere);
		projectile.push<MeshComponent>();
		projectile.push<PhysicsComponent>(Physics::ColliderType::Sphere);
		projectile.get<TransformComponent>()->position = position;

		auto script = projectile.push<ProjectileScript>();
		script->direction = direction;
	}

	OE_DEFINE_CREATOR(PlayerController);
} // namespace Orbital
