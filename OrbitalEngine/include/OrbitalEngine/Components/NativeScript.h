#pragma once

#include "OrbitalTools/Time.h"
#include "OrbitalInputs/Core.h"
#include "OrbitalECS/ECS.h"

#include "OrbitalEngine/Services/ServiceManager.h"

#define OE_DECLARE_CREATOR(CreatorName) \
    extern "C" OSCRIPTS_API Orbital::NativeScript* Create##CreatorName(const Orbital::Entity& e, ScriptServiceManager services)

#define OE_DEFINE_CREATOR(CreatorName) \
namespace Orbital \
{ \
    NativeScript* Create##CreatorName(const Entity& e, ScriptServiceManager services) \
    { \
        return new CreatorName(e, services); \
    } \
}

namespace Orbital
{
    class OENGINE_API NativeScript : public Entity
    {
    public:
        NativeScript(const Entity& e, ScriptServiceManager services);
        virtual ~NativeScript() { }

        virtual void onLoad() { };
        virtual void onStart() { };
        virtual void onUpdate(const Time& dt) { };
        virtual void onCleanUp() { };

    protected:
        ScriptServiceManager mServices;
    };

    typedef NativeScript* CreateNativeScript_t(const Entity& e, ScriptServiceManager services);
}
