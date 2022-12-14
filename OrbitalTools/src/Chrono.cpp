#include "OrbitalTools/Chrono.h"

namespace Orbital
{
	Chrono::Chrono()
	{
	}

	Time Chrono::measure()
	{
		return Time() - mT0;
	}

	void Chrono::reset()
	{
		mT0 = Time();
	}
} // namespace Orbital
