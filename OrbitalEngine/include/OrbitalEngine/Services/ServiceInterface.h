#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/SharedApplication.h"

namespace Orbital
{
	class ServiceInterface
	{
	public:
		ServiceInterface() : mApp()
		{
		}
		ServiceInterface(const SharedApplication& app) : mApp(app)
		{
		}

	protected:
		SharedApplication mApp;
	};
} // namespace Orbital
