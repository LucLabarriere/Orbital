#pragma once

#include "FPSDemoScripts/Context.h"

using namespace Orbital;

namespace FPSDemo
{
	class WeaponPickup : public NativeScript
	{
	public:
		WeaponPickup(const Entity& e);
		virtual ~WeaponPickup(){};

		virtual void onLoad() override;
		virtual void onStart() override;
		virtual void onCreate() override;
		virtual void onPreUpdate(const Time& dt) override;
		virtual void onUpdate(const Time& dt) override;
		OE_SCRIPT_NAME(WeaponPickup);
	};
} // namespace FPSDemo

OE_DECLARE_CREATOR(FPSDEMOSCRIPTS_API, FPSDemo, WeaponPickup);
