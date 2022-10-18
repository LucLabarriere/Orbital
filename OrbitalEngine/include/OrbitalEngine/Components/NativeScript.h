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

        virtual size_t getTypeId() const = 0;

        virtual void onLoad() { };
        virtual void onStart() { };
        virtual void onUpdate(Time dt) { };
    };

    typedef NativeScript* CreateNativeScript_t(const Entity& e);
    typedef size_t GetNativeScriptID_t();
}
