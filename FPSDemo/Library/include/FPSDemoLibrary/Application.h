#pragma once
#include "FPSDemoLibrary/Context.h"

#include "OrbitalEngine/OrbitalApplication.h"

using namespace Orbital;

namespace FPSDemo
{
	class FPSDEMOLIB_API Application: public OrbitalApplication
	{
	public:
		Application();

		virtual void initialize() override;

		virtual bool onKeyPressed(KeyPressedEvent& e) override;
	};
} // namespace FPSDemo
