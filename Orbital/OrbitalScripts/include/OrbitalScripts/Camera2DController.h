#pragma once

#include "OrbitalScripts/Context.h"

using namespace Orbital;

namespace Orbital
{
	class Camera2DController : public NativeScript
	{
	public:
		Camera2DController(const Entity& e);
		virtual ~Camera2DController(){};

		virtual void onLoad() override;
		virtual void onUpdate(const Time& dt) override;

		OE_SCRIPT_NAME(Camera2DController);

	public:
		float translationSpeed = 10.0f;

	private:
		SafeHandle<CameraComponent> mCamera2D;
	};
} // namespace Orbital

OE_DECLARE_CREATOR(ORBITAL_SCRIPTS_API, Orbital, Camera2DController);
