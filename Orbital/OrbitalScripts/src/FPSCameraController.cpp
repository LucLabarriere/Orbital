#include "OrbitalScripts/FPSCameraController.h"

namespace Orbital
{
	FPSCameraController::FPSCameraController(const Entity& baseEntity)
		: NativeScript(baseEntity)
	{
	}

	void FPSCameraController::onLoad()
	{
		mCamera = get<CameraComponent>();
	}

	static Chrono chrono;

	void FPSCameraController::onUpdate(const Time& dt)
	{
		TransformComponent& transform = *get<TransformComponent>();
		CameraComponent& camera = *get<CameraComponent>();
		float position_y = 0.5f;

		Maths::Vec3 cameraFront = camera.getFront();
		// Maths::Vec3 cameraUp = camera.getUp();
		Maths::Vec3 cameraRight = camera.getRight();

		if (Inputs::IsKeyDown(OE_KEY_S)) // Backward
		{
			transform.position -= cameraFront * this->translationSpeed * dt.seconds();
		}

		if (Inputs::IsKeyDown(OE_KEY_W)) // Forward
		{
			transform.position += cameraFront * this->translationSpeed * dt.seconds();
		}

		if (Inputs::IsKeyDown(OE_KEY_A)) // Left
		{
			transform.position -= cameraRight * this->translationSpeed * dt.seconds();
		}

		if (Inputs::IsKeyDown(OE_KEY_D)) // Right
		{
			transform.position += cameraRight * this->translationSpeed * dt.seconds();
		}

		Maths::Vec2 drag = Inputs::GetMouseDrag();

		float rotationSpeed = Settings.Get<float>(Setting::MouseSensitivity);
		auto xAxis = Settings.Get<Maths::Vec3>(Setting::WorldUp) * drag.x *
					 rotationSpeed * dt.seconds();
		auto yAxis =
			Maths::Vec3{ 1.0f, 0.0f, 0.0f } * drag.y * rotationSpeed * dt.seconds();

		transform.rotation += xAxis + yAxis;

		// TODO Move to Maths library
		transform.rotation.x =
			glm::clamp(transform.rotation.x, Maths::Radian(-85.0f), Maths::Radian(85.0f));

		transform.position.y = position_y;
	}
} // namespace Orbital

OE_DEFINE_CREATOR(Orbital, FPSCameraController);
