#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalEngine/SharedApplication.h"

namespace Orbital
{
	/**
	 * @class ServiceInterface
	 * @brief Base class for Service interfaces
	 */
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
