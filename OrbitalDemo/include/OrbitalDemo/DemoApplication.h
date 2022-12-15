#pragma once

#include "OrbitalEngine/OrbitalApplication.h"
#include "OrbitalScripts/Context.h"

namespace Orbital
{
	class DemoApplication : public OrbitalApplication
	{
	public:
		DemoApplication();

		virtual void initialize() override;
		virtual void terminate() override;

		virtual void onLoad() override;
		virtual void preUpdate(const Time& dt) override;
		virtual void update(const Time& dt) override;
		virtual bool onKeyPressed(KeyPressedEvent& e) override;

	private:
		void initializeScripts();
	};
} // namespace Orbital
