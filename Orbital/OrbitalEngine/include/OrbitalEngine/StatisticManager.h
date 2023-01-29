#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/Statistics.h"

namespace Orbital
{
	enum class Statistic;

	class ORBITAL_ENGINE_API StatisticManager
	{
	public:
		StatisticManager();

		template <typename T>
		auto get(Statistic stat) -> T&
		{
			std::any& s = mStatistics[(size_t)stat];

			try
			{
				auto& value = std::any_cast<T&>(s);
				return value;
			}
			catch (const std::bad_any_cast& e)
			{
				Orbital::Assert(
					s.type() == typeid(T),
					std::string("The statistic \"") + StatisticNames[(size_t)stat] +
						"\" was accessed using the incorrect type : " + typeid(T).name()
				);
			}

			return std::any_cast<T&>(s);
		}

		template <typename T>
		auto get(Statistic stat) const -> const T&
		{
			const std::any& s = mStatistics[(size_t)stat];

			try
			{
				const auto& value = std::any_cast<const T&>(s);
				return value;
			}
			catch (const std::bad_any_cast& e)
			{
				Orbital::Assert(
					s.type() == typeid(T),
					std::string("The statistic \"") + StatisticNames[(size_t)stat] +
						"\" was accessed using the incorrect type : " + typeid(T).name()
				);
			}

			return std::any_cast<const T&>(s);
		}

	private:
		std::array<std::any, (size_t)Statistic::SIZE> mStatistics;
	};
} // namespace Orbital
