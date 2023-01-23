#pragma once
#include "DemoLibrary/Context.h"

#include "OrbitalEngine/OrbitalApplication.h"

using namespace Orbital;

namespace Demo
{
	class DEMO_LIB_API Application: public OrbitalApplication
	{
	public:
		Application();

		virtual void onInitialize() override;
	};
} // namespace Demo
