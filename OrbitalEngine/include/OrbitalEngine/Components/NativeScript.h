#pragma once

#include "OrbitalTools/Time.h"
#include "OrbitalInputs/Core.h"
#include "OrbitalECS/ECS.h"

namespace Orbital
{
    class NativeScript : public Entity
    {
    public:
        NativeScript(const Entity& e) : Entity(e) { }
        virtual ~NativeScript() { }

        virtual void onLoad() { };
        virtual void onStart() { };
        virtual void onUpdate(Time dt) { };
    };
}
