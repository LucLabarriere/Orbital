#pragma once

#include "OrbitalScripts/Context.h"

namespace Orbital
{
	class CoreDemoApplication : public NativeScript
	{
	public:
		CoreDemoApplication(const Entity& e);
		virtual ~CoreDemoApplication(){};

		virtual void onLoad() override;
		virtual void onStart() override;
		virtual void onPreUpdate(const Time& dt) override;
		//virtual void onUpdate(const Time& dt) override;
		OE_SCRIPT_NAME(CoreDemoApplication);
	};

	OE_DECLARE_CREATOR(CoreDemoApplication);
} // namespace Orbital
