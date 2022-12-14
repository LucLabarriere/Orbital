#pragma once

#include "OrbitalScripts/Context.h"

namespace Orbital
{{
	class {script_name}: public NativeScript
	{{
	public:
		{script_name}(const Entity& e);
		virtual ~{script_name}(){{}};

		virtual void onLoad() override;
		virtual void onStart() override;
		virtual void onPreUpdate(const Time& dt) override;
		virtual void onUpdate(const Time& dt) override;
		OE_SCRIPT_NAME({script_name});
	}};

	OE_DECLARE_CREATOR({script_name});
}} // namespace Orbital
