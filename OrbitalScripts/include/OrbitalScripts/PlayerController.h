#pragma once

#include "OrbitalScripts/Context.h"
#include "OrbitalTools/Chrono.h"

namespace Orbital
{
	class PlayerController : public NativeScript
	{
	public:
		PlayerController(const Entity& e);
		virtual ~PlayerController(){};

		virtual void onLoad() override;
		virtual void onCreate() override;
		virtual void onPreUpdate(const Time& dt) override;
		virtual void onUpdate(const Time& dt) override;
		OE_SCRIPT_NAME(PlayerController);

		void getHit();
		void spawnProjectile();
		void setSpeed(float value) { mSpeed = value; }

	private:
		float mSpeed;
		int mHealth;
		int mMaxHealth;
		TransformHandle mTransform;
		Chrono mChrono;
		Chrono mRecoveryChrono;
		float mRecoveryTime;
		float mCooldown;
	};

	OE_DECLARE_CREATOR(PlayerController);
} // namespace Orbital
