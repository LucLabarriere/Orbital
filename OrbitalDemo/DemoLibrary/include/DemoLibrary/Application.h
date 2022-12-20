#pragma once
#include "DemoLibrary/Context.h"

#include "OrbitalEngine/OrbitalApplication.h"

using namespace Orbital;

namespace Demo
{
	class Application: public OrbitalApplication
	{
	public:
		Application();

		virtual void initialize() override;

		virtual bool onKeyPressed(KeyPressedEvent& e) override;
	};
} // namespace Demo
