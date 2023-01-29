#include "OrbitalEngine/StatisticManager.h"
#include "OrbitalEngine/Statistics.h"
#include "OrbitalRenderer/Window.h"
#include "OrbitalTools/Errors.h"

namespace Orbital
{
	StatisticManager::StatisticManager() : mStatistics()
	{
		mStatistics[(size_t)Statistic::FPS] = 0.0f;
		mStatistics[(size_t)Statistic::Frametime] = 0.0f;
		mStatistics[(size_t)Statistic::DrawCalls] = 0u;
	}
} // namespace Orbital
