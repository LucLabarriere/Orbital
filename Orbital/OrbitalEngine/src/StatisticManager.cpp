#include "OrbitalEngine/StatisticManager.h"
#include "OrbitalEngine/Statistics.h"
#include "OrbitalRenderer/Window.h"
#include "OrbitalTools/Errors.h"

namespace Orbital
{
	StatisticManager::StatisticManager() : mStatistics()
	{
		mStatistics.reserve((size_t)Statistic::SIZE);

		mStatistics.emplace_back(0.0f); // FPS
		mStatistics.emplace_back(0.0f); // Frametime
		mStatistics.emplace_back(0u);	// Draw calls

		Orbital::Assert(
			mStatistics.size() == (size_t)Statistic::SIZE,
			"The statistics were not properly initialized"
		);
	}
} // namespace Orbital
