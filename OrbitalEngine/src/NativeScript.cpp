#include "OrbitalEngine/Components/NativeScript.h"

namespace Orbital
{
    NativeScript::NativeScript(const Entity& e, ScriptServiceManager services)
        : Entity(e), mServices(services)
    {

    }
}
