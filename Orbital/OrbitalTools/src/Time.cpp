#include "OrbitalTools/Time.h"
#include <chrono>

namespace Orbital
{
	Time::Time()
		: mMicroSeconds(std::chrono::duration_cast<std::chrono::microseconds>(
							std::chrono::steady_clock::now().time_since_epoch()
		  )
							.count())
	{
	}

	Time::Time(float seconds) : mMicroSeconds((int32_t)(seconds * 1000000))
	{
	}
} // namespace Orbital
