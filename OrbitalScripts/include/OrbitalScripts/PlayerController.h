#pragma once

#include "OrbitalScripts/Context.h"

namespace Orbital
{
	class PlayerController : public NativeScript
	{
	public:
		PlayerController(const Entity& e);
		virtual ~PlayerController(){};

		virtual void onLoad() override;
		virtual void onUpdate(const Time& dt) override;
		OE_SCRIPT_NAME(PlayerController);

		void setSpeed(float value) { mSpeed = value; }

	private:
		float mSpeed;
		TransformHandle mTransform;
	};

	OE_DECLARE_CREATOR(PlayerController);
} // namespace Orbital
