#include "FPSDemoScripts/PlayerController.h"
#include "FPSDemoScripts/EnemyScript.h"
#include "FPSDemoScripts/ProjectileScript.h"
#include "FPSDemoScripts/WeaponPickup.h"
#include "FPSDemoLibrary/Components.h"

#include "OrbitalScripts/FreeCameraController.h"

#include "OrbitalPhysics/Colliders.h"

namespace FPSDemo
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
		mTransform->position = Maths::Vec3(0.0f, 0.5f, 0.0f);
		mTransform->scale *= 0.1f;

		auto health = push<Health>();
		health->deathCallback = [this]() { Scenes.Reload(); };

		auto physics = push<PhysicsComponent>(Physics::ColliderType::Sphere);
		auto& collider = physics->getCastedCollider<Physics::SphereCollider>();

		//auto filter = push<MeshFilter>(MeshType::Cube);
		//MeshComponent& m = push<MeshComponent>().get();

		collider.setCollisionCallback(
			[this](Physics::Collider& self, Physics::Collider& other)
			{
				//auto& meshComponent = *get<MeshComponent>();
				auto otherEntity = ECS.GetEntity(other.getID());
				auto pickup = otherEntity.get<WeaponPickup>();

				if (otherEntity.get<EnemyScript>().isValid())
				{
					//meshComponent.setColor({ 1.0f, 1.0f, 1.0f, 1.0f });
					getHit();
				}
			}
		);

		auto cameraComponent = push<CameraComponent>(CameraSpecs{
			.behavior = CameraBehavior::Type::Free,
			.projection = CameraProjection::Type::Perspective,
		});
		Renderer.SetCamera(cameraComponent);

		push<FreeCameraController>();

		mChrono.reset();
		mRecoveryTime = 0.1f;
		this->cooldown = 0.5f;
		this->damage = 0.4f;
	}

	void PlayerController::onPreUpdate(const Time& dt)
	{
		//auto& health = *get<Health>();
		//float color = health.current / health.max;
		//get<MeshComponent>()->setColor({ 1.0f - color, color, 0.0f, 1.0f });
	}

	void PlayerController::onUpdate(const Time& dt)
	{
	}

	void PlayerController::getHit()
	{
		if (mRecoveryChrono.measure().seconds() > mRecoveryTime)
		{
			get<Health>()->getHit(10.0f);
			mRecoveryChrono.reset();
		}
	}
} // namespace FPSDemo

OE_DEFINE_CREATOR(FPSDemo, PlayerController)
