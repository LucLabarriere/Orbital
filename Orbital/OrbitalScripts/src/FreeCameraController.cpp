#include "OrbitalScripts/FreeCameraController.h"

namespace Orbital
{
	FreeCameraController::FreeCameraController(const Entity& baseEntity) : NativeScript(baseEntity)
	{
	}

	void FreeCameraController::onLoad()
	{
		mCamera = get<CameraComponent>();
	}

	static Chrono chrono;

	void FreeCameraController::onUpdate(const Time& dt)
	{
		TransformComponent& transform = *get<TransformComponent>();
		CameraComponent& camera = *get<CameraComponent>();

		Maths::Vec3 cameraFront = camera.getFront();
		Maths::Vec3 cameraUp = camera.getUp();
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

		if (Inputs::IsMouseButtonDown(OE_MOUSE_BUTTON_LEFT) || Inputs::IsMouseButtonDown(OE_MOUSE_BUTTON_RIGHT))
		{
			Maths::Vec2 drag = Inputs::GetMouseDrag();

			auto xAxis = -Maths::Vec3{ 0.0f, 1.0f, 0.0f } * drag.x * this->rotationSpeed * dt.seconds();
			auto yAxis = camera.getRight() * drag.y * this->rotationSpeed * dt.seconds();

			transform.rotation += xAxis + yAxis;

			// TODO Move to Maths library
			transform.rotation.x = glm::clamp(transform.rotation.x, Maths::Radian(-85.0f), Maths::Radian(85.0f));
		}

		if (Inputs::IsKeyDown(OE_KEY_E)) // Up
		{
			transform.position += cameraUp * this->translationSpeed * dt.seconds();
		}

		if (Inputs::IsKeyDown(OE_KEY_Q)) // Down
		{
			transform.position -= cameraUp * this->translationSpeed * dt.seconds();
		}
	}
} // namespace Orbital

OE_DEFINE_CREATOR(Orbital, FreeCameraController);
