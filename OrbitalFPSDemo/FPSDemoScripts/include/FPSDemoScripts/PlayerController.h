#pragma once

#include "FPSDemoScripts/Context.h"

using namespace Orbital;

namespace FPSDemo
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
		void setSpeed(float value)
		{
			mSpeed = value;
		}

		float cooldown;
		float damage;
		Entity camera;

	private:
		float mSpeed;
		TransformHandle mTransform;

		Chrono mChrono;
		Chrono mRecoveryChrono;

		float mRecoveryTime;
	};
} // namespace FPSDemo

OE_DECLARE_CREATOR(FPSDEMOSCRIPTS_API, FPSDemo, PlayerController);
