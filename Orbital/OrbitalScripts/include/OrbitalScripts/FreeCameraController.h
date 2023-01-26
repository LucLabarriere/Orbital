#pragma once

#include "OrbitalScripts/Context.h"

using namespace Orbital;

namespace Orbital
{
	class FreeCameraController : public NativeScript
	{
	public:
		FreeCameraController(const Entity& e);
		~FreeCameraController() override = default;

		void onLoad() override;
		void onUpdate(const Time& dt) override;

		OE_SCRIPT_NAME(FreeCameraController);

	public:
		float translationSpeed = 8.0f;

	private:
		SafeHandle<CameraComponent> mCamera;
	};
} // namespace Orbital

OE_DECLARE_CREATOR(ORBITAL_SCRIPTS_API, Orbital, FreeCameraController)
