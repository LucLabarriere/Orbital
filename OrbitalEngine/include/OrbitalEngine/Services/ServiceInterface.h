#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/SharedApplication.h"

namespace Orbital
{
	class ServiceInterface
	{
	public:
		ServiceInterface(const SharedApplication& app) : mApp(app)
		{
		}

	protected:
		SharedApplication mApp = nullptr;
	};
} // namespace Orbital
