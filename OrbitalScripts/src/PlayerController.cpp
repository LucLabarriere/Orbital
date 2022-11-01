#include "OrbitalScripts/PlayerController.h"
#include "OrbitalEngine/Components/Physics2D.h"
#include "OrbitalEngine/Components/NativeScript.h"

namespace Orbital
{
	PlayerController::PlayerController(const Entity& e, const SharedApplication& app)
		: NativeScript(e, app), mSpeed(10.0f), mTransform(e.get<TransformComponent>())
	{
		mTransform->scale = Maths::Vec3(1.0f, 1.0f, 1.0f) * 0.1f;
	}

	void PlayerController::onLoad()
	{
	}

	void PlayerController::onUpdate(const Time& dt)
	{
		auto dynamics = get<RigidBody2D>();
		auto collider = get<CircleCollider2D>();
		collider->setRadius(mTransform->scale.x / 2);

		mTransform->rotation.z += mSpeed * dt.seconds();

		if (Inputs::IsKeyDown(OE_KEY_Q))
		{
			mTransform->scale -= Maths::Absolute(mSpeed * 0.2f * dt.seconds());
		}

		if (Inputs::IsKeyDown(OE_KEY_E))
		{
			mTransform->scale += mSpeed * dt.seconds();
		}

		if (Inputs::IsKeyDown(OE_KEY_S))
		{
			dynamics->velocity.y -= mSpeed * dt.seconds();
		}

		if (Inputs::IsKeyDown(OE_KEY_W))
		{
			dynamics->velocity.y += mSpeed * dt.seconds();
		}

		if (Inputs::IsKeyDown(OE_KEY_A))
		{
			dynamics->velocity.x -= mSpeed * dt.seconds();
		}

		if (Inputs::IsKeyDown(OE_KEY_D))
		{
			dynamics->velocity.x += mSpeed * dt.seconds();
		}
	}
	OE_DEFINE_CREATOR(PlayerController);
} // namespace Orbital
