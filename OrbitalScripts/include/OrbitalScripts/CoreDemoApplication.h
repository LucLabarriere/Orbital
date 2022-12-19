#pragma once

#include "OrbitalScripts/Context.h"
#include "OrbitalTools/Chrono.h"

namespace Orbital
{
	struct GameEvent
	{
		Chrono chrono;
		float cd;
	};

	class CoreDemoApplication : public NativeScript
	{
	public:
		CoreDemoApplication(const Entity& e);
		virtual ~CoreDemoApplication(){};

		virtual void onLoad() override;
		virtual void onUpdate(const Time& dt) override;
		OE_SCRIPT_NAME(CoreDemoApplication);

	private:
		Entity player;
		GameEvent enemyEvent;
		GameEvent pickupEvent;
	};

	OE_DECLARE_CREATOR(CoreDemoApplication);
} // namespace Orbital
