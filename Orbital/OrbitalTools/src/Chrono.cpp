#include "OrbitalTools/Chrono.h"

namespace Orbital
{
	Chrono::Chrono()
		: mT0()
	{
	}

	const Time& Chrono::measure()
	{
		mMeasurement = Time() - mT0;
		return mMeasurement;
	}

	void Chrono::reset()
	{
		mT0 = Time();
	}
} // namespace Orbital
