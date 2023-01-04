#include "OrbitalScripts/FPSCameraController.h"

namespace Orbital
{
	FPSCameraController::FPSCameraController(const Entity& baseEntity) : NativeScript(baseEntity)
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

		Maths::Vec3 cameraFront = camera.getFront();
		Maths::Vec3 cameraUp = camera.getUp();
		Maths::Vec3 cameraRight = camera.getRight();

		Maths::Vec3 forward = Maths::Normalize({ cameraFront.x, 0.0f, cameraFront.z });
		Maths::Vec3 right = Maths::Normalize({ cameraRight.x, 0.0f, cameraRight.z });

		if (Inputs::IsKeyDown(OE_KEY_S)) // Backward
		{
			transform.position -= forward * this->translationSpeed * dt.seconds();
		}

		if (Inputs::IsKeyDown(OE_KEY_W)) // Forward
		{
			transform.position += forward * this->translationSpeed * dt.seconds();
		}

		if (Inputs::IsKeyDown(OE_KEY_A)) // Left
		{
			transform.position -= right * this->translationSpeed * dt.seconds();
		}

		if (Inputs::IsKeyDown(OE_KEY_D)) // Right
		{
			transform.position += right * this->translationSpeed * dt.seconds();
		}

		Maths::Vec2 drag = Inputs::GetMouseDrag();

		auto xAxis = - Maths::Vec3{0.0f, 1.0f, 0.0f} * drag.x * this->rotationSpeed * dt.seconds();
		auto yAxis = camera.getRight() * drag.y * this->rotationSpeed * dt.seconds();

		transform.rotation += xAxis + yAxis;

		// TODO Move to Maths library
		transform.rotation.x = glm::clamp(transform.rotation.x, Maths::Radian(-85.0f), Maths::Radian(85.0f));

		if (Inputs::IsKeyDown(OE_KEY_E)) // Up
		{
			transform.position += camera.getUp() * this->translationSpeed * dt.seconds();
		}

		if (Inputs::IsKeyDown(OE_KEY_Q)) // Down
		{
			transform.position -= camera.getUp() * this->translationSpeed * dt.seconds();
		}

		// else if (transform.rotation.y < Maths::PI / 2.0f)
		//	transform.rotation.y += Maths::PI / 5.0f;
	}
} // namespace Orbital

OE_DEFINE_CREATOR(Orbital, FPSCameraController);
