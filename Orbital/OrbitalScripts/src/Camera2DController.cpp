#include "OrbitalScripts/Camera2DController.h"

namespace Orbital
{
	Camera2DController::Camera2DController(const Entity& baseEntity)
		: NativeScript(baseEntity)
	{
	}

	void Camera2DController::onLoad()
	{
		mCamera2D = get<CameraComponent>();
	}

	static Chrono chrono;

	void Camera2DController::onUpdate(const Time& dt)
	{
		TransformComponent& transform = *get<TransformComponent>();

		Maths::Vec3 up{ 0.0f, 1.0f, 0.0f };
		Maths::Vec3 right{ 1.0f, 0.0f, 0.0f };

		if (Inputs::IsKeyDown(OE_KEY_S)) // Backward
		{
			transform.position -= up * this->translationSpeed * dt.seconds();
		}

		if (Inputs::IsKeyDown(OE_KEY_W)) // Forward
		{
			transform.position += up * this->translationSpeed * dt.seconds();
		}

		if (Inputs::IsKeyDown(OE_KEY_A)) // Left
		{
			transform.position -= right * this->translationSpeed * dt.seconds();
		}

		if (Inputs::IsKeyDown(OE_KEY_D)) // Right
		{
			transform.position += right * this->translationSpeed * dt.seconds();
		}
	}
} // namespace Orbital

OE_DEFINE_CREATOR(Orbital, Camera2DController);
