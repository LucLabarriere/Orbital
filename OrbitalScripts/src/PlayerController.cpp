#include "OrbitalScripts/PlayerController.h"
#include "OrbitalEngine/ECS/Components/NativeScript.h"
#include "OrbitalEngine/ECS/Components.h"
#include "OrbitalPhysics/Colliders.h"

namespace Orbital
{
	PlayerController::PlayerController(const Entity& e, const SharedApplication& app)
		: NativeScript(e, app), mSpeed(0.3f), mTransform(e.get<TransformComponent>())
	{
		mTransform->scale = Maths::Vec3(1.0f, 1.0f, 1.0f) * 0.1f;
	}

	void PlayerController::onLoad()
	{
	}

	void PlayerController::onUpdate(const Time& dt)
	{
		//auto dynamics = get<RigidBody2D>();
		//auto collider = get<CircleCollider2D>();
		//collider->setRadius(mTransform->scale.x / 2);

		TransformComponent& tempTransform = *mTransform;
		auto collider = get<PhysicsComponent>()->getCastedCollider<Physics::SphereCollider>().lock();

		tempTransform.rotation.z += mSpeed * dt.seconds();

		if (Inputs::IsKeyDown(OE_KEY_Q))
		{
			tempTransform.scale -= Maths::Absolute(mSpeed * 0.2f * dt.seconds());
		}

		if (Inputs::IsKeyDown(OE_KEY_E))
		{
			tempTransform.scale += Maths::Absolute(mSpeed * 0.2f * dt.seconds());
		}

		if (Inputs::IsKeyDown(OE_KEY_S))
		{
			//dynamics->velocity.y -= mSpeed * dt.seconds();
			tempTransform.position.y -= mSpeed * dt.seconds();
		}

		if (Inputs::IsKeyDown(OE_KEY_W))
		{
			//dynamics->velocity.y += mSpeed * dt.seconds();
			tempTransform.position.y += mSpeed * dt.seconds();
		}

		if (Inputs::IsKeyDown(OE_KEY_A))
		{
			//dynamics->velocity.x -= mSpeed * dt.seconds();
			tempTransform.position.x -= mSpeed * dt.seconds();
		}

		if (Inputs::IsKeyDown(OE_KEY_D))
		{
			//dynamics->velocity.x += mSpeed * dt.seconds();
			tempTransform.position.x += mSpeed * dt.seconds();
		}

		collider->setRadius(tempTransform.scale.x / 2.0f);
	}
	OE_DEFINE_CREATOR(PlayerController);
} // namespace Orbital
