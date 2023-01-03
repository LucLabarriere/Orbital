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

		if (Inputs::IsKeyDown(OE_KEY_S)) // Backward
		{
			transform.position -= camera.getForward() * this->translationSpeed;
		}

		if (Inputs::IsKeyDown(OE_KEY_W)) // Forward
		{
			transform.position += camera.getForward() * this->translationSpeed;
		}

		if (Inputs::IsKeyDown(OE_KEY_A)) // Left
		{
			transform.position -= camera.getRight() * this->translationSpeed;
		}

		if (Inputs::IsKeyDown(OE_KEY_D)) // Right
		{
			transform.position += camera.getRight() * this->translationSpeed;
		}

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
		Maths::Vec2 mouseDrag = newMousePosition - mFormerMousePosition;
		mFormerMousePosition = newMousePosition;

		return mouseDrag;
	}
} // namespace Orbital

OE_DEFINE_CREATOR(Orbital, FreeCameraController);
