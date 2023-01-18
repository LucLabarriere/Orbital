#include "OrbitalTools/Chrono.h"

namespace Orbital
{
	Chrono::Chrono()
		: mT0(), mCooldown(1.0f)
	{
	}

	Chrono::Chrono(float cooldown)
		: mT0(), mCooldown(cooldown)
	{

	}

	auto Chrono::measure() -> const Time&
	{
		mMeasurement = Time() - mT0;
		return mMeasurement;
	}

	auto Chrono::ready() -> bool
	{
		if (measure().seconds() > mCooldown)
		{
			reset();
			return true;
		}

		return false;
	}

	void Chrono::reset()
	{
		mT0 = Time();
	}
} // namespace Orbital
