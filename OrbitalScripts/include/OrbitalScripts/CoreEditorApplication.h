#pragma once

#include "OrbitalEngine/ECS/Components/NativeScript.h"
#include "OrbitalScripts/Context.h"

namespace Orbital
{
	class OSCRIPTS_API CoreEditorApplication : public NativeScript
	{
	public:
		CoreEditorApplication(const Entity& e, const SharedApplication& app);

		virtual void onLoad() override;
		virtual void onStart() override;
		virtual void onUpdate(const Time& dt) override;
	};

	OE_DECLARE_CREATOR(CoreEditorApplication);
} // namespace Orbital
