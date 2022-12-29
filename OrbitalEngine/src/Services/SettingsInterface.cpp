#include "OrbitalEngine/Services/SettingsInterface.h"
#include "OrbitalEngine/OrbitalApplication.h"

namespace Orbital
{
	SettingsInterface::SettingsInterface() : ServiceInterface()
	{
	}

	SettingsInterface::SettingsInterface(const SharedApplication& app) : ServiceInterface(app)
	{
	}
	
	void SettingsInterface::Initialize()
	{
		mInstance = mApp.lock()->getSettings();
	}
}
