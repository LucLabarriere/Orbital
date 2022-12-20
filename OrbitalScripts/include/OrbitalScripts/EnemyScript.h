#pragma once

#include "OrbitalScripts/Context.h"
#include "OrbitalTools/Chrono.h"

using namespace Orbital;

class EnemyScript : public Orbital::NativeScript
{
public:
	EnemyScript(const Entity& e);
	virtual ~EnemyScript(){};

	virtual void onLoad() override;
	virtual void onCreate() override;
	virtual void onStart() override;
	virtual void onPreUpdate(const Time& dt) override;
	virtual void onUpdate(const Time& dt) override;
	void setPlayer(const EntityID& playerID)
	{
		mPlayer = ECS.GetEntity(playerID);
	}

	OE_SCRIPT_NAME(EnemyScript);

private:
	Entity mPlayer;
	float mMaxScale;
	float mSpeed;
	float mLifetime;
	Chrono mChrono;
};

OE_DECLARE_CREATOR(EnemyScript);
