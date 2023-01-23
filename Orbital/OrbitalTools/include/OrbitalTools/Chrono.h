#pragma once
#include "OrbitalTools/Time.h"

namespace Orbital
{
	class ORBITAL_TOOLS_API Chrono
	{
	public:
		Chrono();
		Chrono(float cooldown);
		auto measure() -> const Time&;
		auto ready() -> bool;
		void reset();
		void setCooldown(float value) { mCooldown = value; }

		[[nodiscard]] auto getCooldown() const -> float { return mCooldown; }

	private:
		Time mT0;
		Time mMeasurement;
		float mCooldown;
	};
} // namespace Orbital
