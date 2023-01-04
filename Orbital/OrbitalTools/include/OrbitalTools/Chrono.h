#pragma once
#include "OrbitalTools/Time.h"

namespace Orbital
{
	class Chrono
	{
	public:
		Chrono();
		Chrono(float cooldown);
		const Time& measure();
		bool ready();
		void reset();

		void setCooldown(float value) { mCooldown = value; }
		inline float getCooldown() const { return mCooldown; }

	private:
		Time mT0;
		Time mMeasurement;
		float mCooldown;
	};
} // namespace Orbital
