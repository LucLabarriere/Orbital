#pragma once

#include "OrbitalScripts/Context.h"
#include "OrbitalTools/Chrono.h"

namespace Orbital
{
	class SpawnEnemies: public NativeScript
	{
	public:
		SpawnEnemies(const Entity& e);
		virtual ~SpawnEnemies(){};

		virtual void onLoad() override;
		virtual void onStart() override;
		virtual void onCreate() override;
		virtual void onPreUpdate(const Time& dt) override;
		virtual void onUpdate(const Time& dt) override;
		void setPlayer(const EntityID& playerID) { mPlayer = ECS.GetEntity(playerID); }
		OE_SCRIPT_NAME(SpawnEnemies);

	private:
		Chrono mChrono;
		
		float mCoolDown = 0.5f;
		Entity mPlayer;
	};

	OE_DECLARE_CREATOR(SpawnEnemies);
} // namespace Orbital
