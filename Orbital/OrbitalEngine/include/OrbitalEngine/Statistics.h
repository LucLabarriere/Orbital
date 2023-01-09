#pragma once
#include "OrbitalEngine/Context.h"

namespace Orbital
{
	enum class Statistic
	{
		FPS = 0,
		Frametime,
		DrawCalls,
		SIZE,
	};

	static const char* StatisticNames[(size_t)Statistic::SIZE] = { "FPS", "Frame time", "Draw calls", };
	static_assert(sizeof(StatisticNames) / sizeof(const char*) == (size_t)Statistic::SIZE);
} // namespace Orbital
