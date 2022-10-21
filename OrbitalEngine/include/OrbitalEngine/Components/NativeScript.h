#pragma once

#include "OrbitalTools/Time.h"
#include "OrbitalInputs/Core.h"
#include "OrbitalECS/ECS.h"

#define OE_DECLARE_CREATOR(CreatorName) extern "C" OSCRIPTS_API Orbital::NativeScript* Create##CreatorName(const Orbital::Entity& e)
#define OE_DEFINE_CREATOR(CreatorName) namespace Orbital { NativeScript* Create##CreatorName(const Entity& e) { return new CreatorName(e); } }

namespace Orbital
{
    class NativeScript : public Entity
    {
    public:
        NativeScript(const Entity& e) : Entity(e) { }
        virtual ~NativeScript() { }

        virtual void onLoad() { };
        virtual void onStart() { };
        virtual void onUpdate(const Time& dt) { };
        virtual void onCleanUp() { };
    };

    typedef NativeScript* CreateNativeScript_t(const Entity& e);
}
