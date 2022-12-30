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
		OE_SCRIPT_NAME(FreeCameraController);
	};
} // namespace Orbital

OE_DECLARE_CREATOR(ORBITALSCRIPTS_API, Orbital, FreeCameraController);
