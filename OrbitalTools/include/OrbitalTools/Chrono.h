#pragma once
#include "OrbitalTools/Time.h"

namespace Orbital
{
	class Chrono
	{
	public:
		Chrono();
		Time measure();
		void reset();

	private:
		Time mT0;
	};
} // namespace Orbital
