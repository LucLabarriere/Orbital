#pragma once

#include "OrbitalEngine/Services.h"
#include "OrbitalEngine/Services/ServiceInterface.h"
#include "OrbitalEngine/StatisticManager.h"

namespace Orbital
{
	class ORBITAL_ENGINE_API StatisticsInterface : public ServiceInterface
	{
	public:
		StatisticsInterface();
		StatisticsInterface(const SharedApplication& app);

		/**
		 * @brief Initializes the interface
		 */
		void InitializeInterface();

		template <typename T>
		auto Get(Statistic stat) -> T&
		{
			return mInstance.lock()->get<T>(stat);
		}

		template <typename T>
		auto Get(Statistic stat) const -> const T&
		{
			return mInstance.lock()->get<T>(stat);
		}

	private:
		WeakRef<StatisticManager> mInstance;
	};

	OCREATE_SERVICE(Statistics);
} // namespace Orbital
