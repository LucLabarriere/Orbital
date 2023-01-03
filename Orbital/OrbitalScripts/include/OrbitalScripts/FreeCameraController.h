#pragma once

#include "OrbitalScripts/Context.h"

using namespace Orbital;

namespace Orbital
{
	struct GameEvent
	{
		Chrono chrono;
		float cd;
	};

	class FreeCameraController : public NativeScript
	{
	public:
		FreeCameraController(const Entity& e);
		virtual ~FreeCameraController(){};

		virtual void onLoad() override;
		virtual void onUpdate(const Time& dt) override;

		Maths::Vec2 getMouseDrag();

		OE_SCRIPT_NAME(FreeCameraController);

	public:
		float translationSpeed = 0.1f;
		float rotationSpeed = 1.0f;

	private:
		Maths::Vec2 mFormerMousePosition = { 0.0f, 0.0f };
		SafeHandle<CameraComponent> mCamera;
	};
} // namespace Orbital

OE_DECLARE_CREATOR(ORBITALSCRIPTS_API, Orbital, FreeCameraController);
