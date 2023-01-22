#include "OrbitalEngine/Services/StatisticsInterface.h"
#include "OrbitalEngine/OrbitalApplication.h"

namespace Orbital
{
	StatisticsInterface::StatisticsInterface() : ServiceInterface()
	{
	}

	StatisticsInterface::StatisticsInterface(const SharedApplication& app)
		: ServiceInterface(app)
	{
	}

	void StatisticsInterface::InitializeInterface()
	{
		mInstance = mApp.lock()->getStatistics();
	}
} // namespace Orbital
