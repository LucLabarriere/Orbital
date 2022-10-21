#pragma once

#include "OrbitalScripts/Context.h"
#include "OrbitalEngine/Components/NativeScript.h"
#include "OrbitalEngine/Components/TransformComponent.h"
#include "OrbitalEngine/Components/NativeScriptManager.h"

namespace Orbital
{
    class OSCRIPTS_API PlayerController : public NativeScript
    {
        public:
            PlayerController(const Entity& e);
            virtual ~PlayerController() { };
            virtual void onLoad() override;
            virtual void onUpdate(const Time& dt) override;

        private:
            float mSpeed;
            ComponentHandle<TransformComponent> mTransform;
    };

    OE_DECLARE_CREATOR(PlayerController);
}
