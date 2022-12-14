#include "OrbitalScripts/{script_name}.h"
#include "OrbitalEngine/ECS/Components.h"

namespace Orbital
{{
	{script_name}::{script_name}(const Entity& baseEntity)
		: NativeScript(baseEntity)
	{{
	}}

	void {script_name}::onLoad()
	{{
	}}

	void {script_name}::onStart()
	{{
	}}

	void {script_name}::onPreUpdate(const Time& dt)
	{{
	}}

	void {script_name}::onUpdate(const Time& dt)
	{{
	}}

	OE_DEFINE_CREATOR({script_name});

}} // namespace Orbital
