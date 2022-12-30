#pragma once

#include "FPSDemoLibrary/Context.h"
#include "FPSDemoScripts/Context.h"

using namespace Orbital;

namespace FPSDemo
{
	struct GameEvent
	{
		Chrono chrono;
		float cd;
	};

	class CoreScript : public NativeScript
	{
	public:
		CoreScript(const Entity& e);
		virtual ~CoreScript(){};

		virtual void onLoad() override;
		virtual void onUpdate(const Time& dt) override;
		OE_SCRIPT_NAME(CoreScript);

		Entity player;
		Entity camera;
		GameEvent enemyEvent;
		GameEvent pickupEvent;
	};
} // namespace FPSDemo

OE_DECLARE_CREATOR(FPSDEMOSCRIPTS_API, FPSDemo, CoreScript);
