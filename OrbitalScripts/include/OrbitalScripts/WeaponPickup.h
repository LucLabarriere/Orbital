#pragma once

#include "OrbitalScripts/Context.h"

namespace Orbital
{
	class WeaponPickup: public NativeScript
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

	OE_DECLARE_CREATOR(WeaponPickup);
} // namespace Orbital
