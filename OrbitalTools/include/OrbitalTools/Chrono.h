#pragma once
#include "OrbitalTools/Time.h"

namespace Orbital
{
	class Chrono
	{
	public:
		Chrono();
		const Time& measure();
		void reset();

	private:
		Time mT0;
		Time mMeasurement;
	};
} // namespace Orbital
