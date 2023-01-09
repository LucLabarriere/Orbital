#pragma once

#include "OrbitalEngine/Context.h"

namespace Orbital
{
	enum class Statistic;

	class OENGINE_API StatisticManager
	{
	public:
		StatisticManager();

		template <typename T>
		T& get(Statistic setting)
		{
			std::any& s = mStatistics[(size_t)setting];
			Orbital::Assert(s.type() == typeid(T), "The setting was accessed using the incorrect type");
			return std::any_cast<T&>(s);
		}

		template <typename T>
		const T& get(Statistic setting) const
		{
			const std::any& s = mStatistics[(size_t)setting];
			Orbital::Assert(s.type() == typeid(T), "The setting was accessed using the incorrect type");
			return std::any_cast<const T&>(s);
		}

	private:
		std::vector<std::any> mStatistics;
	};
} // namespace Orbital
