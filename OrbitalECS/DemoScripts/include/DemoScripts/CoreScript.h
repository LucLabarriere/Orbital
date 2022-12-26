#pragma once

#include "DemoLibrary/Context.h"
#include "DemoScripts/Context.h"

using namespace Orbital;

namespace Demo
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
} // namespace Demo

OE_DECLARE_CREATOR(DEMOSCRIPTS_API, Demo, CoreScript);
