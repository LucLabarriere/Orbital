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

	const Time& Chrono::measure()
	{
		mMeasurement = Time() - mT0;
		return mMeasurement;
	}

	bool Chrono::ready()
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
