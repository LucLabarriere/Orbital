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

	void FreeCameraController::onUpdate(const Time& dt)
	{
		TransformComponent& transform = *get<TransformComponent>();
		CameraComponent& camera = *get<CameraComponent>();

		float xPos = transform.position.x;
		float yPos = transform.position.y;
		float zPos = transform.position.z;
		Maths::Vec3 cameraFront = camera.getFront();
		Maths::Vec3 cameraUp = camera.getUp();
		Maths::Vec3 cameraRight = camera.getRight();

		Maths::Vec3 forward = Maths::Normalize({ cameraFront.x, 0.0f, cameraFront.z });
		Maths::Vec3 right = Maths::Normalize({ cameraRight.x, 0.0f, cameraRight.z });

		if (Inputs::IsKeyDown(OE_KEY_S)) // Backward
		{
			transform.position -= forward * this->translationSpeed;
		}

		if (Inputs::IsKeyDown(OE_KEY_W)) // Forward
		{
			transform.position += forward * this->translationSpeed;
		}

		if (Inputs::IsKeyDown(OE_KEY_A)) // Left
		{
			transform.position -= right * this->translationSpeed;
		}

		if (Inputs::IsKeyDown(OE_KEY_D)) // Right
		{
			transform.position += right * this->translationSpeed;
		}

		Maths::Vec2 drag = getMouseDrag();
		float dx = drag.y;
		float dy = drag.x;
		transform.rotation += Maths::Vec3(dx, dy, 0.0f);

		//transform.position.y = yPos;

		if (Inputs::IsKeyDown(OE_KEY_E)) // Up
		{
			transform.position += camera.getUp() * this->translationSpeed;
		}

		if (Inputs::IsKeyDown(OE_KEY_Q)) // Down
		{
			transform.position -= camera.getUp() * this->translationSpeed;
		}
	}

	Maths::Vec2 FreeCameraController::getMouseDrag()
	{
		Maths::Vec2 newMousePosition = Inputs::GetScreenSpaceMousePosition();
		Maths::Vec2 mouseDrag = mFormerMousePosition - newMousePosition;
		mFormerMousePosition = newMousePosition;

		return mouseDrag;
	}
} // namespace Orbital

OE_DEFINE_CREATOR(Orbital, FreeCameraController);
