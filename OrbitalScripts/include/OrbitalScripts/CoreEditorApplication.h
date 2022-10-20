#pragma once

#include "OrbitalScripts/Context.h"
#include "OrbitalEngine/Components/NativeScript.h"

namespace Orbital
{
    class CoreEditorApplication: public NativeScript
    {
    public:
        CoreEditorApplication(const Entity& e);

        virtual void onLoad() override;
        virtual void onStart() override;
        virtual void onUpdate(Time& dt) override;
    };

    OE_DECLARE_CREATOR(CoreEditorApplication);
}
