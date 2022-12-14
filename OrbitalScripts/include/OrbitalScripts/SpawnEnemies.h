#pragma once

#include "OrbitalScripts/Context.h"

namespace Orbital
{
	class SpawnEnemies: public NativeScript
	{
	public:
		SpawnEnemies(const Entity& e);
		virtual ~SpawnEnemies(){};

		virtual void onLoad() override;
		virtual void onStart() override;
		virtual void onPreUpdate(const Time& dt) override;
		virtual void onUpdate(const Time& dt) override;
		OE_SCRIPT_NAME(SpawnEnemies);

	private:
		Time mTimeSinceLastEnemySpawned;
		Time mDt;
		float mCoolDown = 0.5f;
	};

	OE_DECLARE_CREATOR(SpawnEnemies);
} // namespace Orbital
