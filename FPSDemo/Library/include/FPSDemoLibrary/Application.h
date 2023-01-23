#pragma once
#include "FPSDemoLibrary/Context.h"

#include "OrbitalEngine/OrbitalApplication.h"

using namespace Orbital;

namespace FPSDemo
{
	class FPSDEMO_LIB_API Application: public OrbitalApplication
	{
	public:
		Application();

		virtual void onInitialize() override;
	};
} // namespace FPSDemo
