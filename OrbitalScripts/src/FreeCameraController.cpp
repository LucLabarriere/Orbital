#include "OrbitalScripts/FreeCameraController.h"

namespace Orbital
{
	FreeCameraController::FreeCameraController(const Entity& baseEntity) : NativeScript(baseEntity)
	{
	}

	void FreeCameraController::onLoad()
	{
	}

	void FreeCameraController::onUpdate(const Time& dt)
	{
		Logger::Debug("Updating camera");
	}
} // namespace Orbital

OE_DEFINE_CREATOR(Orbital, FreeCameraController);
