#pragma once

#include "DemoScripts/Context.h"

using namespace Orbital;

namespace Demo
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

		float damage;
		float speed;

		Chrono fireChrono;
		Chrono recoveryChrono;
		TransformHandle cameraTransform;

	private:
		float mSpeed;
		TransformHandle mTransform;
	};
} // namespace Demo

OE_DECLARE_CREATOR(DEMOSCRIPTS_API, Demo, PlayerController);
