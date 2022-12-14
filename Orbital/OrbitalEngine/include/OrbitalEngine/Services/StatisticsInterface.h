#pragma once

#include "OrbitalEngine/Services.h"
#include "OrbitalEngine/Services/ServiceInterface.h"
#include "OrbitalEngine/StatisticManager.h"

namespace Orbital
{
	class OENGINE_API StatisticsInterface : public ServiceInterface
	{
	public:
		StatisticsInterface();
		StatisticsInterface(const SharedApplication& app);

		/**
		 * @brief Initializes the interface
		 *
		 * @todo Rename to InitializeInterface
		 */
		void InitializeInterface();

		template <typename T>
		T& Get(Statistic stat)
		{
			return mInstance.lock()->get<T>(stat);
		}

		template <typename T>
		const T& Get(Statistic stat) const
		{
			return mInstance.lock()->get<T>(stat);
		}

	private:
		WeakRef<StatisticManager> mInstance;
	};

	OCREATE_SERVICE(Statistics);
} // namespace Orbital
