#pragma once

#include "OrbitalScripts/Context.h"
#include "OrbitalEngine/Components/NativeScript.h"

namespace Orbital
{
    class OSCRIPTS_API CoreEditorApplication: public NativeScript
    {
    public:
        CoreEditorApplication(const Entity& e, ScriptServiceManager services);

        virtual void onLoad() override;
        virtual void onStart() override;
        virtual void onUpdate(const Time& dt) override;
    };

    OE_DECLARE_CREATOR(CoreEditorApplication);
}
