#pragma once

#include "OrbitalScripts/Context.h"

namespace Orbital
{
	class EnemyScript: public NativeScript
	{
	public:
		EnemyScript(const Entity& e);
		virtual ~EnemyScript(){};

		virtual void onLoad() override;
		virtual void onStart() override;
		virtual void onPreUpdate(const Time& dt) override;
		virtual void onUpdate(const Time& dt) override;
		void setPlayer(const EntityID& playerID) { mPlayer = ECS.GetEntity(playerID); }
		OE_SCRIPT_NAME(EnemyScript);

	private:
		unsigned int mHealth;
		Entity mPlayer;
		float mSpeed;
	};

	OE_DECLARE_CREATOR(EnemyScript);
} // namespace Orbital
