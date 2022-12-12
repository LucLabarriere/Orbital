#pragma once

#include "OrbitalScripts/Context.h"

namespace Orbital
{
	class CoreEditorApplication : public NativeScript
	{
	public:
		CoreEditorApplication(const Entity& e, const SharedApplication& app);
		virtual ~CoreEditorApplication(){};

		virtual void onLoad() override;
		virtual void onStart() override;
		virtual void onPreUpdate(const Time& dt) override;
		//virtual void onUpdate(const Time& dt) override;
		OE_SCRIPT_NAME(CoreEditorApplication);
	};

	OE_DECLARE_CREATOR(CoreEditorApplication);
} // namespace Orbital
