#include "OrbitalEngine/Components/NativeScript.h"

namespace Orbital
{
	NativeScript::NativeScript(const Entity& e, const SharedApplication& app) : NativeScriptServices(app), Entity(e)
	{
		NativeScriptServices::InitializeServices();
	}
} // namespace Orbital
