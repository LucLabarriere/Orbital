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

	class FPSCameraController : public NativeScript
	{
	public:
		FPSCameraController(const Entity& e);
		~FPSCameraController() override = default;

		void onLoad() override;
		void onUpdate(const Time& dt) override;

		OE_SCRIPT_NAME(FPSCameraController);

	public:
		float translationSpeed = 10.0f;
		float rotationSpeed = 200.0f;

	private:
		SafeHandle<CameraComponent> mCamera;
	};
} // namespace Orbital

OE_DECLARE_CREATOR(ORBITAL_SCRIPTS_API, Orbital, FPSCameraController)
